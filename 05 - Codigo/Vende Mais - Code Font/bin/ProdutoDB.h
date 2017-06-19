typedef struct PRODUTO {
  char codigo[15];
  char descricao[100];
} produto;

int ValidarCodigoBarras(char * codigo) {
  int i;
  MYSQL_RES *res;
  MYSQL_ROW tupla;

  if(strlen(codigo) > 13)return 0;
  if(strlen(codigo) < 5)return 0;

  for(i=0;i<strlen(codigo);i++)if(!isNumber(codigo[i]))return 0;

  if( !mysql_query ( conexao, "SELECT codigo FROM produto") ){
    res = mysql_store_result(conexao);
    while((tupla = mysql_fetch_row(res))){
      if(strcmp(tupla[0], codigo) == 0) return 2;
    }
  }
  return 1;
}

int InsereProdutoBD(produto novo) {
  char query[200];

  sprintf(query, "INSERT INTO produto (codigo, descricao) VALUES (\"%s\", \"%s\")", novo.codigo, novo.descricao);

  if(!mysql_query(conexao, query))return 1;
  return 0;
}

void GetPrecoProduto(char * codigo){
  float preco;
  char query[100];
  printf("\nDigite o preco para esse produto: ");
  scanf("%f", &preco);
  sprintf(query, "UPDATE precoProduto SET preco = %d WHERE fkProduto = (SELECT idProduto FROM produto WHERE codigo = \'%s\')",(int)preco,  codigo);
  if(!mysql_query(conexao, query)){
    printf("O preco para esse produto foi atualizado com sucesso!\n\n");
  } else {
    printf("Ocorreu o seguinte erro ao atualizar o preco desse produto:\n\n%s\n\nTente novamente\n\n", mysql_error(conexao));
  }
}

void AdicionaProdutoEstoque(char * codigo){
  char query[200];
  sprintf(query, "INSERT INTO produtoEstoque VALUES ((SELECT idProduto FROM produto WHERE codigo = \"%s\"), 0)", codigo);
  mysql_query(conexao, query);
}

void AdicionaPrecoProduto(char * codigo){
  char query[200];
  sprintf(query, "INSERT INTO precoProduto VALUES ((SELECT idProduto FROM produto WHERE codigo = \"%s\"), 0)", codigo);
  mysql_query(conexao, query);
}

void CadastrarProduto() {
  Cabecalho();
  produto novo;
  char op;

  printf("Digite [ 0 ] depois [ ENTER ] a qualquer momento para cancelar.\n\n");

  printf("Digite o C?digo de Barras do Produto: ");
  fflush(stdin);
  fscanf(stdin, "%s", &novo.codigo[0]);
  if(strcmp(novo.codigo, "0")==0)return;

  if(ValidarCodigoBarras(novo.codigo) > 0) {

    printf("Digite o nome e descri??o do produto: ");
    fflush(stdin);
    scanf("%[^\n]", &novo.descricao[0]);
    if(strcmp(novo.descricao, "0")==0)return;

    if(InsereProdutoBD(novo)){
      AdicionaProdutoEstoque(novo.codigo);
      AdicionaPrecoProduto(novo.codigo);
      printf("Produto Cadastrado com sucesso!\n\n");
      printf("Deseja definir um preco de venda desse produto(S/n)?");
      do{
        fflush(stdin);
        op = getch();
        switch (op) {
          case 'S':
          case 's':
          case 13:
          GetPrecoProduto(novo.codigo);
          break;
          case 'N':
          case 'n':
          case 27:
          break;
        }
      } while(op!='S' && op!='s' && op!= 'N' && op!='n' && op!=27 && op!=13);
    }

  } else {
    printf("O c?digo de barras digitado ? inv?lido ou j? foi cadastrado!!\n\n");
  }
}

void ListarTodosProdutos(){
  Cabecalho();
  MYSQL_RES *res;
  MYSQL_ROW tupla;
  int aux = 0;
  printf("Todos Os Produtos\n");
  printf("+---------------+-----------------------------------------------------------------------------+\n");
  if(!mysql_query(conexao, "SELECT codigo, descricao FROM produto")){
    res = mysql_store_result(conexao);
    while ((tupla = mysql_fetch_row(res))) {
      if(!aux){
        printf(" C?d de Barras  | \t\t\t\tDescri??o\n");
        printf("+---------------+-----------------------------------------------------------------------------+\n");
      }
      strlen(tupla[0]) ==13 ? printf(" %s\t| %s\n", tupla[0], tupla[1]) : printf(" %s\t\t| %s\n", tupla[0], tupla[1]);
      aux++;
    }
    if(!aux)printf("\nO cadastro de produtos est? vazio\n\n");
    else printf("+--------------+------------------------------------------------------------------------------+\n");
  } else {
    printf("Ocorreu um erro\n\n%s\n\n", mysql_error(conexao));
  }
}

void ListarProdutosDisponiveis(){
  Cabecalho();
  MYSQL_RES *res;
  MYSQL_ROW tupla;
  int aux = 0;
  printf("Produtos Dispon?veis no Estoque\n");
  printf("+---------------+-------+---------------------------------------------------------------------+\n");
  if(!mysql_query(conexao, "SELECT produto.codigo, produtoEstoque.quantidadeEstoque, produto.descricao FROM produtoEstoque, produto WHERE produto.idProduto = produtoEstoque.fkProduto AND produtoEstoque.quantidadeEstoque > 0")){
    res = mysql_store_result(conexao);
    while ((tupla = mysql_fetch_row(res))) {
      if(!aux){
        printf(" C?d de Barras  | Qtde  | \t\t\tDescri??o\n");
        printf("+---------------+-------+---------------------------------------------------------------------+\n");
      }
      strlen(tupla[0]) ==13 ?
      printf(" %s\t| %d\t| %s\n", tupla[0], atoi(tupla[1]), tupla[2]) :
      printf(" %s\t\t| %s\t| %s\n", tupla[0], tupla[1], tupla[2]);
      aux++;
    }
    if(!aux)printf("\nNenhum Produto Para Exibir\n\n");
    else printf("+--------------+-------+----------------------------------------------------------------------+\n");
  } else {
    printf("Ocorreu um erro\n\n%s\n\n", mysql_error(conexao));
  }
}

void ProdutosEmFalta(){
  Cabecalho();
  MYSQL_RES * res;
  MYSQL_ROW tupla;
  int aux = 0;
  printf("Produto em Falta no Estoque\n");
  printf("+---------------+-----------------------------------------------------------------------------+\n");
  if(!mysql_query(conexao, "SELECT codigo, descricao FROM produto WHERE idProduto IN (SELECT fkProduto FROM produtoEstoque WHERE quantidadeEstoque = 0)")){
    res = mysql_store_result(conexao);
    while ((tupla = mysql_fetch_row(res))) {
      if(!aux){
        printf(" C?d de Barras  |  \t\t\t\tDescri??o\n");
        printf("+---------------+-----------------------------------------------------------------------------+\n");
      }
      strlen(tupla[0]) ==13 ? printf(" %s\t| %s\n", tupla[0], tupla[1]) : printf(" %s\t\t| %s\n", tupla[0], tupla[1]);
      aux++;
    }
    if(!aux)printf("\nNenhum Produto Para Exibir\n\n");
    else printf("+--------------+------------------------------------------------------------------------------+\n");
  } else {
    printf("Ocorreu um erro\n\n%s\n\n", mysql_error(conexao));
  }
}

void PesquisarProduto(){
  Cabecalho();
  MYSQL_RES *res;
  MYSQL_ROW tupla;
  int aux = 0;
  char pesquisa[100], query[250];
  printf("Pesquisar Produto por C?digo de Barras\n\n");
  printf("Digite o C?digo de Barras do Produto desejado: ");
  fflush(stdin);
  gets(pesquisa);
  sprintf(query, "SELECT produto.codigo, produto.descricao, produtoEstoque.quantidadeEstoque, precoProduto.preco FROM produto, produtoEstoque, precoProduto WHERE produto.codigo = \"%s\" AND produto.idProduto = produtoEstoque.fkProduto AND precoProduto.fkProduto = produto.idProduto", pesquisa);
  Cabecalho();
  if(!mysql_query(conexao, query)){
    res = mysql_store_result(conexao);
    while((tupla = mysql_fetch_row(res))){
      if(!aux)
        printf("Resultados da pesquisa: \n\n");
      printf("+---------------------------------------------------------------------------------------------+\n");
      printf("C?digo de Barras:......:%s\n", tupla[0]);
      printf("Descri??o do Produto:..:%s\n", tupla[1]);
      printf("Quantidade no Estoque:.:%s\n", tupla[2]);
      printf("Pre?o de Venda:........:%s\n\n", tupla[3]);
      aux++;
    }
    if(!aux){
      printf("Nenhum Resultado Para Mostrar\n\n");
    }
  }else {
    printf("Aconteceu Um Erro\nProcure o Administrador do Sistema\n\n");
  }
}

int AtualizarPrecoProduto(char * codigo){
  int preco;
  char query[100];
  printf("Digite o novo pre?o para esse produto: ");
  scanf("%d", &preco);
  sprintf(query, "UPDATE precoProduto SET preco = %d WHERE fkProduto = (SELECT idProduto FROM produto WHERE codigo = \'%s\')", preco, codigo);
  if(!mysql_query(conexao, query))
    return 1;
  return 0;
}

void VisualizarPrecoVendaProduto(){
  Cabecalho();
  MYSQL_RES * res;
  MYSQL_ROW tupla;
  int aux = 0;
  char codigo[15];
  if(!mysql_query(conexao, "select produto.codigo, precoProduto.preco, produto.descricao from produto, precoProduto where produto.idProduto = precoProduto.fkProduto")){
    res = mysql_store_result(conexao);
    while((tupla = mysql_fetch_row(res))){
      if(!aux){
        printf("+---------------+-------+---------------------------------------------------------------------+\n");
        printf("  C?d de Barras | Preco |\t\t\tDescri??o\n");
        printf("+---------------+-------+---------------------------------------------------------------------+\n");
      }
      strlen(tupla[0]) ==13 ? printf(" %s\t| %s\t| %s\n", tupla[0], tupla[1], tupla[2]) : printf(" %s\t\t| %s\t| %s\n", tupla[0], tupla[1], tupla[2]);
      aux++;
    }
    printf("+---------------+-------+---------------------------------------------------------------------+\n");
    if(!aux){
      printf("N?o h? nada para mostrar\n\n");
    } else {
      printf("\n\nDigite o C?digo do produto que deseja alterar o preco, ou digite [ enter ] para sair\n->");
      fflush(stdin);
      fscanf(stdin, "%[^\n]", &codigo[0]);
      if(strcmp(codigo, "")==0)return;
      if(ValidarCodigoBarras(codigo)==2){
        if(AtualizarPrecoProduto(codigo))
          printf("O pre?o para do produto foi atualizado com sucesso!!\n\n");
        else
          printf("N?o foi possivel atualizar o pre?o desse produto\n\n%s\n\nTente Novamente\n\n", mysql_error(conexao));
      } else {
        printf("O c?digo digitado ? inv?lido ou n?o est? cadastrado\n\n");
      }
    }
  } else {
    printf("Ocorreu um erro!\n\n%s\n\n", mysql_error(conexao));
  }
}

int AtualizaInformacoesProduto(int id, produto x){
  char query[200];
  sprintf(query, "UPDATE produto SET codigo = \"%s\", descricao = \"%s\" WHERE idProduto = %d", x.codigo, x.descricao, id);
  if(!mysql_query(conexao, query))
    return 1;
  return 0;
}

void EditarProduto(){
  Cabecalho();
  produto x;
  MYSQL_RES * res;
  MYSQL_ROW tupla;
  int aux = 0;
  char codigo[15], op;
  if(!mysql_query(conexao, "SELECT * FROM produto")){
    res = mysql_store_result(conexao);
    while((tupla = mysql_fetch_row(res))){
      if(!aux){
        printf("Digite o c?digo do produto que deseja alterar ou digite [ enter ] para cancelar\n->");
        fflush(stdin);
        fscanf(stdin, "%[^\n]", &codigo[0]);
        if(strcmp(codigo, "")==0)return;
      }
      if(strcmp(codigo, tupla[1])==0){
        Cabecalho();
        printf("Atualizar informa??es de \n %s | %s\n\n", tupla[1], tupla[2]);
        printf("+---------------------------------------------------------------------------------------------+\n");

        printf("C?digo de Barras: %s\nDeseja alterar?(S/n)", tupla[1]);
        do{
          fflush(stdin);
          op = getch();
          switch(op){
            case 'S':
            case 's':
            case 13:
              printf("\nDigite o Novo C?digo de Barras para esse produto ou deixe em branco para cancelar\n->");
              fflush(stdin);
              fscanf(stdin, "%[^\n]", &x.codigo[0]);
              if(strcmp(x.codigo, "")==0)return;
              if(!ValidarCodigoBarras(x.codigo)){
                printf("O c?digo de barras digitado ? inv?lido ou j? est? cadastrado\n\n");
                return;
              }
              break;
            case 'n':
            case 'N':
            case 27:
              strcpy(x.codigo, tupla[1]);
              break;
          }
        }while(op!='S' && op!='S' && op!='n' && op!='N' && op!=13 && op!=27);

        printf("Descri??o: %s\nDeseja Alterar?(S/n)", tupla[2]);
        do{
          fflush(stdin);
          op = getch();
          switch(op){
            case 'S':
            case 's':
            case 13:
              printf("\nDigite uma descri??o para esse produto ou deixe em branco para cancelar\n->");
              fflush(stdin);
              fscanf(stdin, "%[^\n]", &x.descricao[0]);
              if(strcmp(x.descricao, "")==0)return;
              break;
            case 'n':
            case 'N':
            case 27:
              strcpy(x.descricao, tupla[2]);
              break;
          }
        }while(op!='S' && op!='S' && op!='n' && op!='N' && op!=13 && op!=27);

        if(AtualizaInformacoesProduto(atoi(tupla[0]), x))
          printf("Dados atualizados com sucesso!!\n\n");
        else
          printf("Ocorreu o seguinte erro: \n\n%s\n\nTente novamente\n\n", mysql_error(conexao));
        return;
      }
      aux++;
    }
  }
}
