//Definido Variaveis Globais de Conexao
#define HOST "192.168.33.10"
#define USER "vendemais"
#define PASSWORD "1234"
#define DB "merceariafatima"


void ConectDb(){
	system("title Vende Mais - A Sua Ferramenta de Vendas [ conectando...]");
	conexao = mysql_init(NULL);
	
	if(!conexao){
    	printf("ERRO!!\n\nHouve um erro ao iniciar a conexão\n\n");
    	system("pause");
    	exit(0);
	}
	if(!mysql_real_connect(conexao, HOST, USER, PASSWORD, DB, 0, NULL, 0)){
		printf("Erro ao conectar com banco de dados!!\n\n%s", mysql_error(conexao));
		mysql_close(conexao);
    	system("pause");
    	exit(0);
	}
	
}


 