#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <mysql.h>

//Variavel Global Mysql
MYSQL * conexao;

static int userLogged;//armazenara o id do funcionario logado

void about();
void Cabecalho();

#include "bin/db_config.h"
#include "bin/ClienteDB.h"
#include "bin/ProdutoDB.h"
#include "bin/VendaDB.h"
#include "bin/Menu.h"


int main(){
	setlocale(LC_ALL, "");

	ConectDb();
	Login();

	char op;

	do {

		op = menuPrincipal();
		switch (op) {
			case 0:
				about();
				break;
			case 13:break;
			case 27:case '0':
				printf("\n\nEncerrando Conexão...\n\n");
				Cabecalho();
				printf("Tenha Um Bom Dia!!\n");
				Sleep(1000);
			break;
			case '1':
				menuVendas();
			break;
			case '2':
				menuFornecedor();
			break;
			case '3':
				menuCliente();
			break;
			case '4':
				menuEstoque();
			break;
		}
	} while(op!='0' && op!=27);

	mysql_close(conexao);
	system("exit");
	return 0;
}
