#include <iostream>
#include <string>
#include <cstdio>
#include <locale>

using namespace std;

FILE *Arq;

struct Nascimento {
	int dia, mes, ano;
};

struct Cadastro_Aluno {
	int cod;
	char nome[30], gen[10];
	Nascimento nasc;
};

struct Entrada_Apostila {
	int nome;
	float preco;
	int quantidade;
};

void MENU();
void Alunos();
void Cad_alunos();
void Buscar_alunos();
void Excluir_alunos();
void Rel_alunos();
void Apostilas();
void Entrada_Epostilas();
void Rel_apostilas();

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Portuguese");

//	Arq = fopen("Alunos.dat","wb");
//	Arq = fopen("Apostilas.dat","wb");
//	fclose(Arq);

	MENU();

	return 0;
}

//menu principal
void MENU() {

	system("cls");

	int op, opmenu;

	cout << "-----------------------" << endl;
	cout << "GERENCIAMENTO DA ESCOLA" << endl;
	cout << "-----------------------" << endl;

	cout << "\nEscolha uma das opções abaixo" << endl;
	cout << "-------------------------------" << endl;

	cout << "(1) GERENCIAR ALUNOS" << endl;
	cout << "(2) GERENCIAR APOSTILAS" << endl;
	cout << "\n(0) FECHAR" << endl;
	cout << "\nOpção: ";

	cin >> op;
	cin.ignore(); // Limpar buffer

	switch (op) {
		case 1:
			Alunos();
			break;
		case 2:
			Apostilas();
			break;
		case 0:
			return;
		default:
			system("cls");
			cout << "Opção inválida!" << endl;
			cout << "Voltar para o menu? (Digite 1 para 'SIM' ou 0 para 'NÃO'):" << endl;

			cin >> opmenu;

			if (opmenu == 1) {
				MENU();
			} else {
				return;
			}
			break;
	}
}

//menu para alunos
void Alunos() {

	system("cls");

	int op;

	cout << "--------------------------" << endl;
	cout << " GEERENCIAMENTO DE ALUNOS " << endl;
	cout << "--------------------------" << endl;

	cout << "\n(1) CADASTRAR ALUNO(S)";
	cout << "\n(2) BUSCAR ALUNO(S)";
	cout << "\n(3) EXCLUIR ALUNO(S)";
	cout << "\n(4) RELATÓRIO GERAL" << endl;
	cout << "\n(0) MENU INICIAL" << endl;

	cout << "\nDigite a opção que deseja: ";
	cin >> op;
	cin.ignore();

	switch (op) {
		case 1:
			Cad_alunos();
			break;
		case 2:
			Buscar_alunos();
			break;
		case 3:
			Excluir_alunos();
			break;
		case 4:
			Rel_alunos();
			break;
		case 0:
			MENU();
			break;
		default:
			system("cls");
			cout << "Opção inválida" << endl;
			system("pause");
			Alunos();
			break;
	}
}

//Cadastrar alunos
void Cad_alunos(){

	system("cls");

	Cadastro_Aluno cadal;

	int ver;

	Arq = fopen("Alunos.dat", "ab");
	
	if (Arq == NULL) {
		cout << "Erro na abertura do arquivo" << endl;
		system("pause");
		exit(1);
	}

	cout << "--------------------" << endl;
	cout << " GADASTRO DE ALUNOS " << endl;
	cout << "--------------------" << endl;

	do {
		cout << "Informe o código: ";
		cin >> cadal.cod;
		cin.ignore();

		cout << "Informe o nome: ";
		cin.getline(cadal.nome, 30);

		cout << "Informe o genero: ";
		cin.ignore();
		cin >> cadal.gen;

		cout << "Informe a data de nascimento: " << endl;
		cout << "Dia: ";
		cin >> cadal.nasc.dia;

		cout << "Mês: ";
		cin >> cadal.nasc.mes;

		cout << "Ano: ";
		cin >> cadal.nasc.ano;

		fwrite(&cadal, sizeof(cadal), 1, Arq);

		cout << "\nDeseja cadastrar outro aluno? (Digite 1 para 'SIM' ou 0 para 'NÃO'): ";
		cin >> ver;
		cin.ignore();
	} while (ver == 1);

	fclose(Arq);

	Alunos();
}

//Buscar alunos
void Buscar_alunos() {

	system("cls");

	Cadastro_Aluno cadal;

	int codigo;

	cout << "-----------------" << endl;
	cout << " BUSCA DE ALUNOS " << endl;
	cout << "-----------------" << endl;

	cout << "\nDigite o código do aluno que deseja buscar: ";
	cin >> codigo;

	Arq = fopen("Alunos.dat", "rb");

	if (Arq == NULL) {
		cout << "Nenhum aluno cadastrado!" << endl;
		system("pause");
		exit(1);
		return;
	}

	while(fread(&cadal, sizeof(cadal), 1, Arq) > 0) {
		if(codigo == cadal.cod) {

			cout << "\nInformações do aluno" << endl;
			cout << "----------------------" << endl;

			cout << "Código: " << cadal.cod << endl;
			cout << "Nome: " << cadal.nome << endl;
			cout << "Gênero: " << cadal.gen << endl;
			cout << "Nascimento: " << cadal.nasc.dia << "/" << cadal.nasc.mes << "/" << cadal.nasc.ano << endl;
			cout << "-------------------------" << endl;

			cout << "Pressione ENTER para sair" << endl;

			system("pause>>null");
			fclose(Arq);

			return Alunos();
		}
	}

	cout << "Aluno não encontrado" << endl << endl;;

	cout << "Pressione ENTER para sair" << endl;

	system("pause>>null");
	fclose(Arq);

	Alunos();
}

//Excluir alunos
void Excluir_alunos() {

	system("cls");

	Cadastro_Aluno cadal;
	int cod;
	bool encontrou = false;

	cout << "Informe o código do aluno que deseja excluir: ";
	cin >> cod;

	Arq = fopen("Alunos.dat", "r+b");

	if (Arq == NULL) {
		cout << "Nenhum aluno cadastrado!" << endl;
		system("pause");
		return;
	}

	// Posição atual no arquivo
	long posicao = 0;

	while(fread(&cadal, sizeof(cadal), 1, Arq) > 0) {
		if(cod == cadal.cod) {
			// Voltar para a posição deste registro
			fseek(Arq, posicao, SEEK_SET);

			// Marcar como excluído (código = 0)
			cadal.cod = 0;

			// Escrever o registro modificado de volta
			fwrite(&cadal, sizeof(cadal), 1, Arq);

			// Forçar escrita no disco
			fflush(Arq);

			cout << "Aluno excluído com sucesso" << endl;
			encontrou = true;
			break;
		}
		// Atualizar a posição para o próximo registro
		posicao = ftell(Arq);
	}

	if (!encontrou) {
		cout << "Aluno não encontrado!" << endl;
	}

	cout << "Pressione ENTER para sair" << endl;
	fclose(Arq);

	system("pause>>null");
	Alunos();
}

//Relatorio geral de alunos
void Rel_alunos() {

	system("cls");

	Cadastro_Aluno cadal;

	Arq = fopen("Alunos.dat", "rb");

	if (Arq == NULL) {
		cout << "Nenhum aluno cadastrado!" << endl;
		system("pause");
		exit(1);
		return;
	}

	cout << "RELATÓRIO GERAL DE ALUNOS" << endl;
	cout << "-------------------------" << endl;

	while(fread(&cadal, sizeof(cadal), 1, Arq) > 0) {

		if(cadal.cod != 0) {
			cout << "Código: " << cadal.cod << endl;
			cout << "Nome: " << cadal.nome << endl;
			cout << "Gênero: " << cadal.gen << endl;
			cout << "Nascimento: " << cadal.nasc.dia << "/" << cadal.nasc.mes << "/" << cadal.nasc.ano << endl;
			cout << "-------------------------" << endl;
		}
	}

	cout << "Pressione ENTER para sair" << endl;

	system("pause>>null");
	fclose(Arq);

	Alunos();
}

void Apostilas() {

	system("cls");

	int op, opmenu;

	cout << "--------------------------" << endl;
	cout << "GERENCIAMENTO DE APOSTILAS" << endl;
	cout << "--------------------------" << endl;

	cout << "\n(1) ENTRADA DE APOSTILAS";
	cout << "\n(2) RELATÓRIO GERAL" << endl;
	cout << "\n(0) MENU INICIAL" << endl;

	cout << "\nDigite a opção que deseja: ";
	cin >> op;

	switch(op) {
		case 1:
			Entrada_Epostilas();
			break;
		case 2:
			Rel_apostilas();
			break;
		case 0:
			MENU();
			break;
		default:
			system("cls");
			cout << "Opção inválida!" << endl;
			cout << "Voltar para o menu? (Digite 1 para 'SIM' ou 0 para 'NÃO'):" << endl;

			cin >> opmenu;

			if (opmenu == 1) {
				MENU();
			} else {
				return;
			}
			break;
	}
}

void Entrada_Epostilas() {

	system("cls");

	Entrada_Apostila entrada;

	int ver;

	Arq = fopen("Apostilas.dat", "ab");

	cout << "----------------------" << endl;
	cout << " ENTRADA DE APOSTILAS " << endl;
	cout << "----------------------" << endl;

	if (Arq == NULL) {
		cout << "Erro na abertura do arquivo" << endl;
		system("pause");
		exit(1);
	}

	do {

		cout << "\nInformações do livro: " << endl;
		cout << "\nNúmero: ";
		cin >> entrada.nome;
		cout << "\nPreço: ";
		cin >> entrada.preco;
		cout << "\nQuantidade: ";
		cin >> entrada.quantidade;

		fwrite(&entrada, sizeof(entrada), 1, Arq);

		cout << "\n\nDeseja dar entrada em outro(s) livrro(s)? (Digite 1 para 'SIM' ou 0 para 'NÃO'): ";
		cin >> ver;
		cin.ignore();
	} while (ver == 1);

	fclose(Arq);
	Apostilas();
}

void Rel_apostilas() {

	system("cls");

	Entrada_Apostila entrada;

	Arq = fopen("Apostilas.dat", "rb");

	if (Arq == NULL) {
		cout << "Nenhum aluno cadastrado!" << endl;
		system("pause");
		exit(1);
		return;
	}

	cout << "RELATORIO APOSTILAS: " << endl;
	cout << "-------------------------" << endl;

	while(fread(&entrada, sizeof(entrada), 1, Arq) > 0) {

		cout << "Número: " << entrada.nome << endl;
		cout << "Preço: " << entrada.preco << endl;
		cout << "Quantidade: " << entrada.quantidade << endl;
		cout << "Total pago: " << (entrada.preco * entrada.quantidade) << endl;
		cout << "-------------------------" << endl;
	}
	cout << "Pressione ENTER para sair" << endl;

	system("pause>>null");
	fclose(Arq);

	Apostilas();
}
