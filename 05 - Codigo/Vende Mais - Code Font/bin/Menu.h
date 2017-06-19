void Cabecalho() {
  system("color 1f");
  system("cls");
  printf("***********************************************************************************************");
  printf("\n\
*   *   ** *    ___ ___                 __          _______         __	              *     *    \n\
*  *    * *    |   |   |.-----.-----.--|  |.-----. |   |   |.---.-.|__|.-----. 	*     *   ** *\n\
*   *  *   *   |   |   ||  -__|     |  _  ||  -__| |       ||  _  ||  ||__ --|     *     *   ** *\n\
*  *    *  *    \\_____/ |_____|__|__|_____||_____| |__|_|__||___._||__||_____|    *     *   ** *\n\
\n");
  printf("***************************** A SUA FERRAMENTA DE VENDAS. *************************************\n\n");
}

void about(){
  system("title Vende Mais - A Sua Ferramenta de Vendas [ About... ]");
  system("cls");
  printf("***********************************************************************************************");
  printf("\n\
*     *   *  *    ___ ___                 __          _______         __  *     *      *      *\n\
*  *    *   *    |   |   |.-----.-----.--|  |.-----. |   |   |.---.-.|__|.-----.        * *   *\n\
* *  *  *  * *   |   |   ||  -__|     |  _  ||  -__| |       ||  _  ||  ||__ --|    *      *  *\n\
*   *    *   *    \\_____/ |_____|__|__|_____||_____| |__|_|__||___._||__||_____|  *   *   *   *\n");
  printf("*                                                                                             *\n");
  printf("*         Essa ferramenta foi criada como parte do projeto GRULES realizado pela              *\n");
  printf("*   Faculdades Unificadas de Teófilo Otoni. Consiste em uma ferramenta básica para auxiliar   *\n");
  printf("*       pequenos comerciantes em suas tarefas diárias de vendas e controle de estoque.        *\n");
  printf("*                                                                                             *\n");
  printf("*                                        CREDITOS                                             *\n");
  printf("*                          PESQUISA E LEVANTAMENTO DE REQUISITOS:                             *\n");
  printf("*                                      Ycaro Gonçalves                                        *\n");
  printf("*                                                                                             *\n");
  printf("*                                MODELAGEM DO BANCO DE DADOS:                                 *\n");
  printf("*                                      Ycaro Gonçalves                                        *\n");
  printf("*                                       Josemar Silva                                         *\n");
  printf("*                                                                                             *\n");
  printf("*                                ANÁLISE E VALIDAÇÃO DO BD:                                   *\n");
  printf("*                                      Patrick Silva                                          *\n");
  printf("*                                         Eric Alves                                          *\n");
  printf("*                                      Joyce Caldeiras                                        *\n");
  printf("*                                                                                             *\n");
  printf("*                                         BACK END                                            *\n");
  printf("*                                      Josemar Silva                                          *\n");
  printf("*                                                                                             *\n");
  printf("*                                        FRONT  END                                           *\n");
  printf("*                                      Patrick Silva                                          *\n");
  printf("*                                                                                             *\n");
  printf("*                                 ANÁLISE E AJUSTES FINAIS                                    *\n");
  printf("*                                      Joyce Caldeiras                                        *\n");
  printf("*                                         Eric Alves                                          *\n");
  printf("*                                                                                             *\n");
  printf("*                                                        Todos os Direitos Reservados - 2017  *\n");
  printf("***********************************************************************************************\n");
  system("pause");
}

int GrantAcess(char * user, char * password){
  MYSQL_RES * res;
  MYSQL_ROW tupla;
  char query[100] = {""};
  sprintf(query, "SELECT * FROM logins WHERE user = \'%s\' AND passwd = \'%s\' ", user, password);
  if(!mysql_query(conexao, query)){
    res = mysql_store_result(conexao);
    if((tupla = mysql_fetch_row(res)))return (atoi(tupla[0]));
    else return 0;
  } else {
    printf("ERRO!\n\n%s\n\n", mysql_error(conexao));
    return -1;
  }
}

void Login(){
  char user[20], password[10] = {""};
  int count = 0, GA, aux, i;

  do{
    system("title Vende Mais - A Sua Ferramenta de Vendas [ Login ]");
    Cabecalho();
    if(count)printf("\n\nUsuário ou senha incorreto\n\nTente Novamente\n");
    printf("\n\n***********************************************************************************************\n");
    printf("\t\t\tÉ Necessario fazer login\n\n");
    printf("Digite o usuário: ");
    fflush(stdin);
    gets(user);
    printf("\nDigite a senha: ");
    i = 0;
    do{
      aux = getch();
      fflush(stdin);
      if(aux==13)continue;
      if(aux==8){
        i--;
      } else {
        password[i] = aux;
        printf("*");
        i++;
      }
    }while(aux != 13);

    GA = GrantAcess(user, password);

    if(GA < 0){
      getch();
      exit(0);
    }
    if(GA){
      userLogged = GA;
      return;
    }
    count++;
  }while(count<5);

  exit(0);
}


char menuPrincipal() {
	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Principal ]");
    Cabecalho();

    char op;
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf(" [1] Vendas | [2] Fornecedor | [3] Cliente | [4] Estoque | [0] Sair do Sistema | [ F10 ] Sobre\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Escolha uma opção:\n\n");
    fflush(stdin);
    op = getch();
    return op;
}

void menuVendas() {
  char op;

	do{
      system("title Vende Mais - A Sua Ferramenta de Vendas [ Vendas ]");
	    Cabecalho();
	    printf("\
Menu Venda\n\n\
[ 1 ] - Realizar Nova Venda\n\
[ 2 ] - Visualizar Todas As Vendas\n\
[ 3 ] - Detalhar Venda\n\
[ 4 ] - Notinhas Vencidas\n\
[ 5 ] - Notinhas Pendentes\n\
[ 0 ] - Menu Principal\n\n\
Escolha Uma Opção: ");

		op = getch();
	    switch (op) {
		    case '0':case 27:return;break;
		    case '1':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Vendas - Nova Venda ]");
		        printf("Realizar Nova Venda\n\n");
            NovaVenda();
		        break;
		    case '2':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Vendas - Todas as Vendas ]");
		        printf("Visualizar Todas as Vendas\n\n");
            ListarVendas();
		        break;
        case '3':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Vendas - Detalhar Venda ]");
            printf("Detalhar Venda\n\n");
            break;
		    case '4':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Vendas - Notinhas Vencidas ]");
		        printf("Notinhas Vencidas\n\n");
		        break;
		    case '5':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Vendas - Notinhas Pendentes ]");
		        printf("Notinhas Próximo do Vencimento\n\n");
		        break;
	    }
	    system("pause");
	}while(op!='0' && op!=27);
}

void menuFornecedor() {
  char op;

	do{
      system("title Vende Mais - A Sua Ferramenta de Vendas [ Fornecedor ]");
    	Cabecalho();
    	printf("\
Menu Fornecedores\n\n\
[ 1 ] - Cadastrar Novo Fornecedor\n\
[ 2 ] - Listar Todos os Fornecedores Ativos Cadastrados\n\
[ 3 ] - Pesquisar Fornecedores Por Nome ou CNPJ\n\
[ 4 ] - Telefones Fornecedores\n\
[ 5 ] - Fornecedores Com Notas Em Aberto\n\
[ 0 ] - Menu Principal\n\n\
Escolha Uma Opção: ");

		op = getch();
	    switch (op) {
		    case '0':case 27:return;break;
		    case '1':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Fornecedor - Cadastrar Novo ]");
		        printf("Cadastrar Novo Fornecedor\n\n");
		        system("pause");
		        break;
		    case '2':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Fornecedor  - Fornecedores Ativos]");
		        printf("Listar Fornecedores Ativos\n\n");
		        break;
		    case '3':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Fornecedor  - Buscar ]");
		        printf("Pesquisar Fornecedor por Nome ou CNPJ\n\n");
		        break;
		    case '4':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Fornecedor  - Telefones ]");
		        printf("Telefones Fornecedores\n\n");
		        break;
		    case '5':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Fornecedor - Notas Em Aberto ]");
		        printf("Fornecedores Com Notas Em Aberto\n\n");
		        break;
		}
	    system("pause");
	}while(op!='0' && op!=27);
}

void menuCliente() {
	char op;

	do{
      system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente ]");
	    Cabecalho();
    	printf("\
Menu Cliente\n\n\
[ 1 ] - Cadastrar Cliente\n\
[ 2 ] - Listar Todos Clientes Ativos Cadastrados\n\
[ 3 ] - Pesquisar Cliente Por Nome ou CPF\n\
[ 4 ] - Telefones Clientes\n\
[ 5 ] - Clientes Com Notas Pendentes\n\
[ 6 ] - Clientes Com Notas Vencidads\n\
[ 7 ] - Atualizar Dados De Clientes\n\
[ 8 ] - Ativar/Desativar Cliente\n\
[ 9 ] - Remover Cliente\n\
[ 0 ] - Menu Principal\n\n\
Escolha Uma Opção: ");
		fflush(stdin);

	   	op = getch();
	   	Cabecalho();
	    switch (op) {
		    case 27:case '0':return;break;
		    case '1':
	   	   		system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente - Cadastrar Novo Cliente ]");
		        printf("Cadastrar Cliente\n\n");
		        cadastrarCliente();
		        break;
		    case '2':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente - Listar Todas ]");
		        printf("Listar Todos\n\n");
		        listarClientes();
		        system("pause");
		        break;
		    case '3':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente - Pesquisar]");
		        printf("Pesquisar Cliente Por Nome ou CPF\n\n");
		        pesquisarCliente();
		        system("pause");
		        break;
		    case '4':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente - Contato ]");
		        printf("Telefones Cliente\n\n");
		        telefonesCliente();
		        system("pause");
		        break;
		    case '5':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente - Notinhas Pendentes ]");
		        printf("Clientes Com Notinhas Pendentes\n\n");
            clientesDevedores();
            system("pause");
		        break;
		    case '6':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente - Notinhas Vencidas ]");
		        printf("Clientes Com Notinhas Vencidas\n\n");
            clientesImpedidos();
            system("pause");
		        break;
		    case '7':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente - Atualizar Dados ]");
		        printf("Atualizar Dados De Clientes\n\n");
		        atualizarDadosCliente();
		        system("pause");
		        break;
		    case '8':
        	  system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente - Status ]");
		        printf("Ativar Desativar Cliente\n\n");
		        break;
		    case '9':
          	system("title Vende Mais - A Sua Ferramenta de Vendas [ Cliente - Remover ]");
  		    	printf("Remover Cliente\n\n");
  		    	removerCliente();
  		    	system("pause");
  		    	break;
	    }
	} while(op!='0' && op!=27);
}

void menuEstoque(){
  char op;

  do{
    system("title Vende Mais - A Sua Ferramenta de Vendas [ Estoque ]");
  	Cabecalho();
		printf("\
Menu Estoque\n\n\
[ 1 ] - Cadastrar Novo Produto\n\
[ 2 ] - Listar Todos Os Produtos Cadastrados\n\
[ 3 ] - Listar Produtos No Estoque\n\
[ 4 ] - Listar Produtos Em Falta\n\
[ 5 ] - Pesquisar Produto por Codigo de Barras\n\
[ 8 ] - Visualizar/Atualizar Preço de Venda de Produtos\n\
[ 9 ] - Editar Informações de Produtos\n\
[ 0 ] - Menu Principal\n\n\
Escolha Uma Opção: ");
		op = getch();

		switch (op) {
			case '0':case 27:return;break;
			case '1':
        system("title Vende Mais - A Sua Ferramenta de Vendas [ Estoque - Cadastrar Produto ]");
				printf("Cadastrar Novo Produto\n\n");
				CadastrarProduto();
			break;
			case '2':
        system("title Vende Mais - A Sua Ferramenta de Vendas [ Estoque - Listar Todos os Produtos ]");
				printf("Listar Todos os Produtos Cadastrados\n\n");
				ListarTodosProdutos();
			break;
			case '3':
        system("title Vende Mais - A Sua Ferramenta de Vendas [ Estoque - Produtos Disponíveis no Estoque ]");
				printf("Produtos Disponíveis No Estoque\n\n");
				ListarProdutosDisponiveis();
			break;
			case '4':
        system("title Vende Mais - A Sua Ferramenta de Vendas [ Estoque - Produtos em Falta ]");
				printf("Produtos Em Falta No Estoque\n\n");
        ProdutosEmFalta();
			break;
			case '5':
        system("title Vende Mais - A Sua Ferramenta de Vendas [ Estoque - Buscar Produto ]");
				printf("Pesquisar Produto por Código de Barras\n\n");
        PesquisarProduto();
			break;
			case '8':
        system("title Vende Mais - A Sua Ferramenta de Vendas [ Estoque - Preços Produto ]");
				printf("Visualizar/Atualizar Preço de Venda de Produtos\n\n");
        VisualizarPrecoVendaProduto();
			break;
			case '9':
        system("title Vende Mais - A Sua Ferramenta de Vendas [ Estoque - Editar Produto ]");
				printf("Editar Informações de Produtos");
        EditarProduto();
			break;
		}
	    system("pause");
	}while(op!='0' && op!=27);
}
