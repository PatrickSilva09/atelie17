void ListarVendas(){
  MYSQL_RES * res;
  MYSQL_ROW tupla;
  char temp[5];

  if(!mysql_query(conexao, "SELECT venda.idVenda, cliente.nome, funcionario.nome, venda.dataVenda, venda.valor, (select descricao from produto where produtoVenda.fkProduto = produto.idProduto) as produto, produtoVenda.quantidade, produtoVenda.precoUnidade, (produtoVenda.quantidade * produtoVenda.precoUnidade) as subtotal FROM venda, cliente, produtoVenda, produto, funcionario WHERE cliente.idCliente = venda.fkCliente AND venda.fkFuncionario = funcionario.idFuncionario and produto.idProduto = produtoVenda.fkProduto and produtoVenda.fkVenda = venda.idVenda order by idVenda")){
    res = mysql_store_result(conexao);

    tupla = mysql_fetch_row(res);
    if(tupla){
      strcpy(temp, tupla[0]);
      printf("Venda %s\n", tupla[0]);
      printf("+--------------------------------------------------------------------------------------+\n");
      printf("Cliente......: %s\n", tupla[1]);
      printf("Funcion?rio..: %s\n", tupla[2]);
      printf("Data Venda...: %s\n", tupla[3]);
      printf("Valor........: R$ %s\n", tupla[4]);
      printf("+------+----------+----------+---------------------------------------------------------+\n");
      printf("  Qtde | PrecoUni | Subtotal | \t\tProduto\n");
      printf("+------+----------+----------+---------------------------------------------------------+\n");
      printf("  %s   | %s\t\t| %.2f \t| %s\n", tupla[6], tupla[7], atof(tupla[8]), tupla[5]);
    } else {
      printf("Nada para mostrar\n\n");
      return;
    }

    while((tupla = mysql_fetch_row(res))){
      if(strcmp(temp, tupla[0])){
        strcpy(temp, tupla[0]);
        printf("+--------------------------------------------------------------------------------------+\n\n");
        printf("Venda %s\n", tupla[0]);
        printf("+--------------------------------------------------------------------------------------+\n");
        printf("Cliente......: %s\n", tupla[1]);
        printf("Funcion?rio..: %s\n", tupla[2]);
        printf("Data Venda...: %s\n", tupla[3]);
        printf("Valor........: R$ %s\n", tupla[4]);
        printf("+------+----------+----------+---------------------------------------------------------+\n");
        printf("  Qtde | PrecoUni | Subtotal | \t\tProduto\n");
        printf("+------+----------+----------+---------------------------------------------------------+\n");
        printf("  %s   | %s\t\t| %.2f \t| %s\n", tupla[6], tupla[7], atof(tupla[8]), tupla[5]);
      } else {
        printf("  %s   | %s\t\t| %.2f \t| %s\n", tupla[6], tupla[7], atof(tupla[8]), tupla[5]);
      }


    }
    printf("+------+----------+----------+---------------------------------------------------------+\n");
  } else {
    printf("Ocorreu o seguinte erro:\n\n%s\n\n", mysql_error(conexao));
    return;
  }
}

int IniciarNovaCompra(){
  MYSQL_RES *res;
  MYSQL_ROW tupla;
  char query[150];
  sprintf(query, "INSERT INTO venda (fkCliente, fkFuncionario, dataVenda, valor) VALUES (1, %d, curdate(), 0)", userLogged);
  if(!mysql_query(conexao, query)){
    mysql_query(conexao, "SELECT LAST_INSERT_ID()");
    res = mysql_store_result(conexao);
    tupla = mysql_fetch_row(res);
    if(tupla)
      return atoi(tupla[0]);
  }
  return 0;
}

float PrecoProduto(char * codigo, int qtde){
  MYSQL_RES * res;
  MYSQL_ROW tupla;
  char query[150];
  sprintf(query, "SELECT ( %d * preco ) FROM precoProduto WHERE fkProduto = (SELECT idProduto FROM produto WHERE codigo = \'%s\')", qtde, codigo);
  if(!mysql_query(conexao, query)){
    res = mysql_store_result(conexao);
    tupla = mysql_fetch_row(res);
    return (atof(tupla[0]));
  }
  return 0;
}

void MostrarProdutosListaVenda(int idVenda){
  MYSQL_RES *res;
  MYSQL_ROW tupla;
  char query[150];
  sprintf(query, "SELECT quantidade, precoUnidade, (SELECT descricao FROM produto WHERE idProduto = fkProduto) FROM produtoVenda WHERE fkVenda = %d", idVenda);
  if(!mysql_query(conexao, query)){
    res = mysql_store_result(conexao);
    while((tupla = mysql_fetch_row(res))){
      printf(" %s\t| %s\t| %.2f | %s\n", tupla[0], tupla[1], ( (atoi(tupla[0])) * (atof(tupla[1])) ), tupla[2]);
    }
  }
}

void CancelaVenda(int idVenda){}

void InsereProdutoVenda(int idVenda, char * codigo, int qtde){
  char query[300];
  sprintf(query, "INSERT INTO produtoVenda VALUES (%d, (SELECT idProduto FROM produto WHERE codigo = \'%s\'), %d, (SELECT preco FROM precoProduto WHERE fkProduto = (SELECT idProduto FROM produto WHERE codigo = \'%s\')))", idVenda, codigo, qtde, codigo);
  if(mysql_query(conexao, query)){
    printf("Ocorreu um erro ao inserir esse produto\n\n%s\n\n", mysql_error(conexao));
    system("pause");
  }
  sprintf(query, "UPDATE produtoEstoque SET quantidadeEstoque = quantidadeEstoque - %d WHERE fkProduto = (SELECT idProduto FROM produto WHERE codigo = \'%s\')", qtde, codigo);
  mysql_query(conexao, query);
}

void NovaVenda(){
  Cabecalho();
  int idVenda, qtde;
  float total = 0;
  char codigo[15], op, cpf[13]={""}, query[200];

  if(!(idVenda = IniciarNovaCompra())){
    printf("N?o Foi poss?vel Iniciar uma Nova venda\n\n%s\n\nTente Novamente\n\n", mysql_error(conexao));
    return;
  }

  while(1){
    Cabecalho();
    printf("ID Desta Venda: %d\tTotal: %.2f\n", idVenda, total);
    printf("+--------------------------------------------------------------------------------------+\n");
    printf("  qtde | preco | subtotal | \t\t\tProduto\n");
    printf("+--------------------------------------------------------------------------------------+\n");
    MostrarProdutosListaVenda(idVenda);
    printf("\n\nDigite o C?digo de barras do produto para adicionar | [ 1 ] Para Finalizar | [ 0 ] Para Cancelar a venda\n->");
    fflush(stdin);
    gets(codigo);

    if(strcmp(codigo, "1")==0)break;
    if(strcmp(codigo, "0")==0){CancelaVenda(idVenda);return;}

    if(ValidarCodigoBarras(codigo)==2){
      printf("Qual a quantidade: ");
      scanf("%d", &qtde);

      InsereProdutoVenda(idVenda, codigo, qtde);

      total += PrecoProduto(codigo, qtde);
    } else {
      printf("O c?digo digitado ? inv?lido\n\n");
      system("pause");
    }

  }

  sprintf(query, "UPDATE venda SET valor = %d WHERE idVenda = %d", (int)total, idVenda);
  mysql_query(conexao, query);

  do{
    Cabecalho();
    printf("ID Desta Venda: %d\tTotal: %.2f\n", idVenda, total);
    printf("+--------------------------------------------------------------------------------------+\n");
    printf("Venda a Vista ou a Prazo?\n[ 1 ] A VISTA\n[ 2 ] A prazo\n");
    do{
      op = getch();
    }while(op!=13&&op!='1'&&op!='2');
    switch (op) {
      case '1':case 13:
        printf("Digite o CPF do Cliente (ou pode deixe em branco):\n->");
        fflush(stdin);
        fscanf(stdin, "%[^\n]", &cpf[0]);
        if(strcmp(cpf, "")==0){
          printf("Venda a Vista concluida!\n\n");
          break;
        }
        if(!cpfRepetido(cpf)){
          op = 10;
          printf("CPF n?o encontrado!\n\n");
        }
        else{
          sprintf(query, "UPDATE venda SET fkCliente = (SELECT idCliente FROM cliente WHERE cpf = \'%s\') WHERE idVenda = %d", cpf, idVenda);
          if(!mysql_query(conexao, query)){
            printf("Venda a vista concluida!\n\n");
            break;
          } else {
            printf("Houve um erro ao finalizar Essa venda\n\n%s\n\n", mysql_error(conexao));
          }
        }
      break;
      case '2':

      break;
    }
  }while(op!=13&&op!='1'&&op!='2');
}
