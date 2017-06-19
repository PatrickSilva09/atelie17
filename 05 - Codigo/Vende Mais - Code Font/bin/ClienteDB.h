void getTelefones(char * cpf, char * nome);

typedef struct CLIENTE{
  char cpf[12];
  char nome[46];
  int diaNascimento, mesNascimento, anoNascimento;
  int limiteCredito;
} cliente;

void mostraCliente(MYSQL_ROW linha){
	printf("  %s | %s |\t%s\t| %s\n", linha[0], linha[1], linha[2], linha[3]);
}

int isNumber(char x){
	if(x == '0'||x == '1'||x == '2'||x == '3'||x == '4'||x == '5'||x == '6'||x == '7'||x == '8'||x == '9')return 1;
	return 0;
}

int telefoneValido(char * telefone){
	int i;
	for(i = 0; i<strlen(telefone); i++)if(!isNumber(telefone[i]))return 0;//verifica se ha caracteres nao permitidos no telefone
	if(strlen(telefone) < 8 && strlen(telefone) > 11)return 0;
	return 1;
}

int cpfRepetido(char * cpf){
	MYSQL_RES *res;
	MYSQL_ROW tupla;

	if( !mysql_query ( conexao, "SELECT cpf, nome FROM cliente") ){
		res = mysql_store_result(conexao);

		while((tupla = mysql_fetch_row(res))){
      if(strcmp(tupla[1], "Avulso") != 0){
		    if(strcmp(tupla[0], cpf) == 0)
          return 1; /*cpf ja cadastrado*/
      }
		}
	}
	return 0;
}

int ValidarCpf(char * cpf){
	int i;

	for( i=0; i < strlen(cpf); i++) if ( !isNumber( cpf[i] ) ) return 0;/*cpf com caractere nao permitido*/

	if( strlen( cpf ) < 10 || strlen( cpf ) > 11 ) return 0;/*cpf maior ou menor que o tamanho permitido*/

	return 1;
}

int insereCliente(cliente x){
	char query[150];

	snprintf(query, sizeof(query), "INSERT INTO cliente(cpf, nome, dataNascimento, limiteCredito) VALUES (\"%s\", \"%s\", \"%.4d-%.2d-%.2d\", default)", x.cpf, x.nome, x.anoNascimento, x.mesNascimento, x.diaNascimento);

	if(!mysql_query(conexao, query)) return 1;

	return 0;
}

int insereTelefoneCliente(char * cpf, char * telefone){
  char query[150];

  sprintf(query, "INSERT INTO telefonesCliente VALUES ((SELECT idCliente FROM cliente WHERE cpf = \"%s\"), \"%s\") ", cpf, telefone);

  if(!mysql_query(conexao, query)) return 1;

  return 0;
}

void cadastrarCliente(){
	char op;
	cliente novo;
	Cabecalho();

	printf("Digite [ 0 ] depois [ ENTER ] a qualquer momento para cancelar.\n\n");

	printf("Digite o CPF do Cliente: ");
	fflush(stdin);
	fscanf(stdin, "%s", &novo.cpf[0]);

	if(novo.cpf[0] == '0') return;

	if(ValidarCpf(novo.cpf) && !cpfRepetido(novo.cpf)){
		printf("Digite o Nome do Cliente: ");
		fflush(stdin);
    	scanf("%[^\n]", &novo.nome[0]);

		if(strlen(novo.nome)==1 && novo.nome[0]=='0') return;
			printf("Data de Nascimento\n\tDia: ");
    		scanf("%d", &novo.diaNascimento);

			if(novo.diaNascimento==0)return;
			printf("\tM?s: ");
    		scanf("%d", &novo.mesNascimento);

			if(novo.mesNascimento==0)return;
			printf("\tAno: ");
    		scanf("%d", &novo.anoNascimento);

			if(novo.anoNascimento==0)return;

			if(( novo.diaNascimento < 0 || novo.diaNascimento > 31 || novo.mesNascimento < 0 || novo.mesNascimento > 12) || ( novo.diaNascimento > 29 && novo.mesNascimento == 2 ) || ((novo.diaNascimento==31) && (novo.mesNascimento==2 || novo.mesNascimento==4 || novo.mesNascimento==6 || novo.mesNascimento==9 || novo.mesNascimento==11))){
				printf("A data digitada ? inv?lida!\n\n");
				return;
			}

			if(novo.anoNascimento>=1 && novo.anoNascimento<=99)
				novo.anoNascimento = novo.anoNascimento+1900;

		if( insereCliente( novo ) ){
			Cabecalho();
			printf("\t\tCliente cadastrado com sucesso!\n Deseja cadastrar algum telefone para esse cliente?(S / N)");

			do{
				fflush(stdin);
		        op = getch();

				switch(op){
					case 's':
					case 'S':
					case 13:
						getTelefones(novo.cpf, novo.nome);
					break;

					case 'n':
					case 'N':
					case 27:
					break;

					default:
						printf("Deseja cadastrar algum telefone para esse cliente?(S/n)");
				}
			}while( op!='n' && op!='N' && op!='S' && op!='s' && op!=13 && op!=27 );
	    } else {
			printf("Ocorreu o seguinte erro ao cadastrar o novo cliente:\n\n%s\n\nTente Novamente\n\n", mysql_error(conexao));
	    }
	} else {
    	printf("CPF inv?lido ou j? cadastrado! Tente Novamente\n\n");
	}
	system("pause");
}

void getTelefones(char * cpf, char * nome){
	Cabecalho();
	char telefone[13];

	while(1){
		printf("Cadastrar Novo Telefone Para: %s\n\n", nome);
    	printf("Digite um n?mero de telefone(DDD+N?mero) ou deixe em branco para finalizar: ");
		fflush(stdin);
    	gets(telefone);

		Cabecalho();

		if(strcmp(telefone, "")==0)return;

		if(telefoneValido(telefone)){
  	  	  if(insereTelefoneCliente(cpf, telefone))
			printf("N?mero cadastrado com sucesso!\n\n");
  	  	  else
    		printf("Ocorreu O seguinte erro ao tentar cadastrar esse telefone:\n\n%s\n\n", mysql_error(conexao));
		} else {
  	  	  printf("O n?mero de telefone digitado n?o ? v?lido\nTente Novamente\n\n");
		}
	}
}

void listarClientes(){
  MYSQL_RES *res;
  MYSQL_ROW tupla;
  int aux = 0;
  if(!mysql_query(conexao, "SELECT cpf, dataNascimento, limiteCredito, nome FROM cliente")){
    res = mysql_store_result(conexao);
    while((tupla = mysql_fetch_row(res))){
    	if(!aux){
		    printf("+-------------+------------+------------+----------------------------------------------+\n");
		    printf("      CPF     | Nascimento |   Limite   |                     NOME\n");
		    printf("+-------------+------------+------------+----------------------------------------------+\n");
		}
    if(strcmp(tupla[3], "Avulso"))
		mostraCliente(tupla);
		aux++;
    }

    if(aux)printf("+-------------+------------+-----------+-----------------------------------------------+\n");
    else printf("O cadastro de clientes est? vazio\n\n");

  } else {
    printf("Aconteceu Um Erro\nProcure o Administrador do Sistema\n\n");
  }
}

void pesquisarCliente(){
  MYSQL_RES *res;
  MYSQL_ROW tupla;
  int i;
  char pesquisa[47], query[150];
  printf("Digite o Nome ou CPF do Cliente desejado: ");
  fflush(stdin);
  gets(pesquisa);
  sprintf(query, "SELECT cpf, dataNascimento, limiteCredito, nome FROM cliente WHERE nome like \"%%%s%%\" OR cpf = \"%s\"", pesquisa, pesquisa);
  if(!mysql_query(conexao, query)){
    for(i=0;;i++){
      res = mysql_store_result(conexao);
      while((tupla = mysql_fetch_row(res))){
        if(i==0){
          printf("+-------------+------------+------------+----------------------------------------------+\n");
          printf("      CPF     | Nascimento |   Limite   |                     NOME\n");
          printf("+-------------+------------+------------+----------------------------------------------+\n");
          i++;
        }
        if(strcmp(tupla[3], "Avulso"))
        mostraCliente(tupla);
      }
      printf("+-------------+------------+------------+----------------------------------------------+\n\n");
      break;
    }
    if(i==0){
      system("cls");
      printf("Nenhuma Correspond?ncia\n\n");
    }
  } else {
    printf("Aconteceu Um Erro\nProcure o Administrador do Sistema\n\n");
  }
}

void telefonesCliente() {
    MYSQL_RES *res;
    MYSQL_ROW tupla;
    char clienteAtual[47];
    if(!mysql_query(conexao, "SELECT cliente.nome AS cliente, telefonesCliente.telefone FROM cliente, telefonesCliente WHERE cliente.idCliente = telefonesCliente.fkCLiente ORDER BY cliente")){
        res = mysql_store_result(conexao);
        tupla = mysql_fetch_row(res);
        while(tupla){
            if(strcmp(clienteAtual, tupla[0])!=0){
                strcpy(clienteAtual, tupla[0]);
                printf("\n--------------------------------------------------\n");
                printf("%s\n", clienteAtual);
                printf("--------------------------------------------------\n");
            }
            printf("\t%s\n", tupla[1]);
            tupla = mysql_fetch_row(res);
        }
        printf("--------------------------------------------------\n\n\n");
    }
}

void clientesDevedores(){
  MYSQL_RES * res;
  MYSQL_ROW tupla;
  int aux = 0;
  char cpfTemp[13];
  if(!mysql_query(conexao, "SELECT cliente.cpf, cliente.nome as Cliente, venda.dataVenda as DataCompra, notinha.dataVencimento as DataVencimento, venda.valor as ValorNota, telefonesCliente.telefone FROM cliente, venda, notinha, telefonesCliente WHERE cliente.idCliente = venda.fkCliente AND cliente.idCliente = telefonesCliente.fkCliente AND venda.idVenda = notinha.fkVenda AND notinha.status = 'n' AND notinha.dataVencimento >= curdate()")){

    res = mysql_store_result(conexao);
    tupla = mysql_fetch_row(res);

    if(tupla)strcpy(cpfTemp, tupla[0]);

    printf("+---------------+----------------------------------------------------------------------+\n");
    printf("  %s   | %s\n", tupla[0], tupla[1]);
    printf("+---------------+----------------------------------------------------------------------+\n");
    printf("Data da Compra..: %s\n", tupla[2]);
    printf("Vencimento......: %s\n", tupla[3]);
    printf("Valor Notinha...: %s\n", tupla[4]);
    printf("Telefone........:");

    while(tupla){
      if(strcmp(cpfTemp, tupla[0])){
        strcpy(cpfTemp, tupla[0]);
        printf("\n\n\n+---------------+----------------------------------------------------------------------+\n");
        printf("  %s   | %s\n", tupla[0], tupla[1]);
        printf("+---------------+----------------------------------------------------------------------+\n");
        printf("Data da Compra..: %s\n", tupla[2]);
        printf("Vencimento......: %s\n", tupla[3]);
        printf("Valor Notinha...: %s\n", tupla[4]);
        printf("Telefone........: %s /", tupla[5]);
      } else {
        printf(" %s /", tupla[5]);
      }
      tupla = mysql_fetch_row(res);
      aux++;
    }
    if(!aux){
      printf("N?o h? Clientes com notinhas Pendentes\n\n");
    }
  }
  printf("\n\n");
}

void clientesImpedidos(){
  MYSQL_RES * res;
  MYSQL_ROW tupla;
  int aux = 0;
  char cpfTemp[13];
  if(!mysql_query(conexao, "SELECT cliente.cpf, cliente.nome as Cliente, venda.dataVenda as DataCompra, notinha.dataVencimento as DataVencimento, venda.valor as ValorNota, telefonesCliente.telefone FROM cliente, venda, notinha, telefonesCliente WHERE cliente.idCliente = venda.fkCliente AND cliente.idCliente = telefonesCliente.fkCliente AND venda.idVenda = notinha.fkVenda AND notinha.status = 'n' AND notinha.dataVencimento < curdate()")){

    res = mysql_store_result(conexao);
    tupla = mysql_fetch_row(res);

    if(tupla)strcpy(cpfTemp, tupla[0]);

    printf("+---------------+----------------------------------------------------------------------+\n");
    printf("  %s   | %s\n", tupla[0], tupla[1]);
    printf("+---------------+----------------------------------------------------------------------+\n");
    printf("Data da Compra..: %s\n", tupla[2]);
    printf("Vencimento......: %s\n", tupla[3]);
    printf("Valor Notinha...: %s\n", tupla[4]);
    printf("Telefone........:");

    while(tupla){
      if(strcmp(cpfTemp, tupla[0])){
        strcpy(cpfTemp, tupla[0]);
        printf("\n\n\n+---------------+----------------------------------------------------------------------+\n");
        printf("  %s   | %s\n", tupla[0], tupla[1]);
        printf("+---------------+----------------------------------------------------------------------+\n");
        printf("Data da Compra..: %s\n", tupla[2]);
        printf("Vencimento......: %s\n", tupla[3]);
        printf("Valor Notinha...: %s\n", tupla[4]);
        printf("Telefone........: %s /", tupla[5]);
      } else {
        printf(" %s /", tupla[5]);
      }
      tupla = mysql_fetch_row(res);
      aux++;
    }
    if(!aux){
      printf("N?o h? Clientes com notinhas Vencidas\n\n");
    }
  }
  printf("\n\n");
}

void atualizarDadosPessoais(MYSQL_ROW tupla){
	int id = atoi(tupla[0]);
	char query[200];
	char op, tempDia[2], tempMes[2], tempAno[4];
	cliente alterado;
	Cabecalho();
	printf("Alterando dados de %s\n\n", tupla[2]);
	printf("CPF atual: %s\nDeseja alterar?(S/n)", tupla[1]);

	do{
		op = getch();
		switch(op){
			case 's':case 'S':case 13:
				printf("\nDigite o novo CPF : ");
				fflush(stdin);
				gets(alterado.cpf);
				if(!ValidarCpf(alterado.cpf) || cpfRepetido(alterado.cpf)){
					printf("\nCPF ? inv?lido ou j? foi cadastrado\nVerifique os dados e tente novamente\n");
					return;
				}
			break;
			case 'n':case 'N':case 27:
				strcpy(alterado.cpf, tupla[1]);
			break;
		}
	}while(op!='S'&&op!='s'&&op!='N'&&op!='n'&&op!=13&&op!=27);

	printf("\n\nNome atual: %s\nDeseja alterar?(S/n)", tupla[2]);
	do{
		op = getch();
		switch(op){
			case 's':case 'S':case 13:
				printf("\nDigite o nome: ");
				fflush(stdin);
				gets(alterado.nome);
			break;
			case 'n':case 'N':case 27:
				strcpy(alterado.nome, tupla[2]);
			break;
		}
	}while(op!='S'&&op!='s'&&op!='N'&&op!='n'&&op!=13&&op!=27);

	printf("\n\nData de Nascimento Cadastrado: %s\nDeseja alterar?(S/n)", tupla[3]);
	do{
		op = getch();
		switch(op){
			case 's':case 'S':case 13:
				printf("\nData de Nascimento:\n\t");
				printf("Dia: ");
				scanf("%d", &alterado.diaNascimento);
				printf("\tMes: ");
				scanf("%d", &alterado.mesNascimento);
				printf("\tAno: ");
				scanf("%d", &alterado.anoNascimento);
			break;
			case 'n':case 'N':case 27:
				alterado.anoNascimento = atoi(memcpy(tempAno, &tupla[3][0], 4));
				alterado.mesNascimento = atoi(memcpy(tempMes, &tupla[3][5], 2));
				alterado.diaNascimento = atoi(memcpy(tempDia, &tupla[3][8], 2));
			break;
		}
	}while(op!='S'&&op!='s'&&op!='N'&&op!='n'&&op!=13&&op!=27);
	printf("\n\nLimite de Credito Atual: %.2f\nDeseja alterar?(S/n)", (float)atof(tupla[4]));
	do{
		op = getch();
		switch(op){
			case 's':case 'S':case 13:
				printf("\nNovo Limite de Credito para %s: ", alterado.nome);
				scanf("%d", &alterado.limiteCredito);
			break;
			case 'n':case 'N':case 27:
				alterado.limiteCredito = (float)atof(tupla[4]);
			break;
		}
	}while(op!='S'&&op!='s'&&op!='N'&&op!='n'&&op!=13&&op!=27);
	sprintf(query, "UPDATE cliente SET cpf = \'%s\', nome = \'%s\', dataNascimento = \'%d-%d-%d\', limiteCredito = %d WHERE idCliente = %d", alterado.cpf, alterado.nome, alterado.anoNascimento, alterado.mesNascimento, alterado.diaNascimento, alterado.limiteCredito, id);
	Cabecalho();
	if(!mysql_query(conexao, query))
		printf("Os dados foram alterados!!\n\n");
	else
		printf("Ocorreu o seguinte erro ao tentar alterar os dados: \n%s\n\nTente Novamente\n\n", mysql_error(conexao));
}

int atualizaTelefoneCliente(int id, char * numeroAntigo, char * numeroNovo){
	char query[100];
	sprintf(query, "UPDATE telefonesCliente SET telefone = \'%s\' where fkCliente = %d AND telefone = \'%s\'", numeroNovo, id, numeroAntigo);
	if(!mysql_query(conexao, query))
		return 1;
	return 0;
}

int removeTelefoneBD(int idCliente, char * telefone){
	char query[100];
	sprintf(query, "DELETE FROM telefonesCliente WHERE fkCliente = %d AND telefone = \'%s\'", idCliente, telefone);
	if(!mysql_query(conexao, query))
		return 1;
	return 0;
}

void atualizarContato(MYSQL_ROW tupla){
	int id = (int)(atoi(tupla[0]));
	char query[100];
	char telefone[11];
	MYSQL_RES *res;
	MYSQL_ROW linha;
	int q = 0;
	char op;
	Cabecalho();
	printf("Alterando telefones de contato de %s\n\n", tupla[2]);
	sprintf(query, "SELECT * FROM telefonesCliente WHERE fkCliente = %d", id);
	if(!mysql_query(conexao, query)){
		res = mysql_store_result(conexao);
		while((linha = mysql_fetch_row(res))){
			printf("Telefone%d: %s\nVoc? deseja:\n[ 1 ] Adicionar Novo\n[ 2 ] Alterar\n[ 3 ] Remover\n[ esc ] Cancelar\n", q+1, linha[1]);
			do{
				op = getch();
				switch(op){
          case '1':
            getTelefones(tupla[1], tupla[2]);
            break;
  				case '2':
  					printf("Digite o n?mero: ");
  					fflush(stdin);
  					gets(telefone);
  					if(telefoneValido(telefone)){
  						if(atualizaTelefoneCliente(id, linha[1], telefone))
  							printf("Telefone alterado com sucesso!!\n\n");
  						else
  							printf("Ocorreu o seguinte erro:\n%s\nTente Novamente\n\n", mysql_error(conexao));
  					} else {
  						printf("O n?mero digitado n?o ? v?lido\nTente novamente\n\n");
  					}
  					break;
  				case '3':
  					if(removeTelefoneBD(id, linha[1]))
  						printf("Telefone removido!\n\n");
  					else
  						printf("Ocorreu o seguinte erro:\n%s\nTente Novamente\n\n", mysql_error(conexao));
  				break;
  				case 27:
  					break;
  				}
        }while(op!='1'&&op!='2'&&op!='3'&&op!=27);
        q++;
      }
      if(q==0){
			printf("N?o h? nenhum telefone cadastrado para esse cliente\n\nDeseja adicionar agora(S/n)?\n");
			do{
				op = getch();
				switch(op){
				case 's':case 'S':case 13:
					getTelefones(tupla[1], tupla[2]);
					break;
				case 'n':case 'N':case 27:
					break;
				}
			}while(op!='S'&&op!='s'&&op!='n'&&op!='N'&&op!=13&&op!=27);
		}
	} else {
		printf("Ocorreu o seguinte erro ao buscar telefones para esse cliente:\n\n%s\n\nTente Novamente\n\n", mysql_error(conexao));
	}
}

char escolhaAlteracao(char * nome){
	char op;
	do{
		Cabecalho();
		printf("Quais dados de %s voc? deseja alterar?\n\n", nome);
		printf("[ 1 ] Dados Pessoais\n");
		printf("[ 2 ] Telefones de Contato\n");
		printf("[ esc ] Cancelar\n");
		op = getch();
	} while(op!='1' && op!='2' && op!='c' && op!='C' && op!=27);
	return op;
}

void atualizarDadosCliente(){
	Cabecalho();
	printf("Atualizar Dados de Cliente\n\n");
	char cpf[11];
	char query[150];
	char aux;
	MYSQL_RES *res;
	MYSQL_ROW tupla;
	printf("Digite o CPF do Cliente que voc? deseja Alterar(ou deixe em branco para sair):");
	fflush(stdin);
	gets(cpf);
	if(strlen(cpf)==0)return;
	sprintf(query, "SELECT idCliente, cpf, nome, dataNascimento, limiteCredito FROM cliente WHERE cpf = \"%s\"", cpf);
	if(!mysql_query(conexao, query)){
		res = mysql_store_result(conexao);
		if((tupla = mysql_fetch_row(res))){
			aux = escolhaAlteracao(tupla[2]);
			switch(aux){
				case '1':
					atualizarDadosPessoais(tupla);
				break;
				case '2':
					atualizarContato(tupla);
				break;
				case 'c':case 'C':case 27:return;break;

			}
		} else {
			printf("CPF n?o encontrado\nVerifique os dados e tente novamente\n\n");
		}
	} else {
		printf("Ocorreu o seguinte erro ao tentar recuperar esse cliente: \n\n%s\n\nTente Novamente\n\n", mysql_error(conexao));
	}
}

int removeClienteDB(int idCliente){
	char query[100];
	sprintf(query, "DELETE FROM cliente WHERE idCliente = %d", idCliente);
	if(!mysql_query(conexao, query))return 1;
	return 0;
}

void removerCliente(){
	char cpf[11], query[100];
	MYSQL_RES *res;
	MYSQL_ROW tupla;
	Cabecalho();
	printf("Remover Cliente\n\n");
	printf("Digite o CPF do cliente que voc? deseja remover: ");
	fflush(stdin);
	gets(cpf);
	if(ValidarCpf(cpf)){
		sprintf(query, "SELECT idCliente FROM cliente WHERE cpf = \'%s\'", cpf);
		if(!mysql_query(conexao, query)){
			res = mysql_store_result(conexao);
			if((tupla = mysql_fetch_row(res))){
				if(removeClienteDB((int)atoi(tupla[0])))
					printf("Cliente Removido com sucesso!!\n\n");
				else
					printf("N?o foi possivel remover esse cliente\nErro:\n\n%s\n\nTente Novamente\n\n", mysql_error(conexao));
			}
			else
				printf("O CPF n?o foi encontrado\nVerifique os dados e tente novamente\n\n");
		} else {
			printf("Ocorreu um erro!!\n\n%s\n\nTente Novamente\n\n", mysql_error(conexao));
		}
	} else {
		printf("O n?mero de CPF digitado ? inv?lido\nVerifique os dados e tente novamente\n\n");
	}
}
