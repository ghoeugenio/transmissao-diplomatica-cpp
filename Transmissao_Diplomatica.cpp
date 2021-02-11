#include <iostream>
#include <time.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

void fflush_stdin(){//limpar o buffer do teclado
	int ch;
	while((ch = getchar()) != '\n' && ch != EOF);
}

typedef struct{
	string assunto;
	string mensagem;
	int ordem;
	int h[3];//0 - hora | 1 - minuto | 2 - segundo
	bool tipo;//false - recebida| true - enviada
	int vizualizada;//0 - nao | 1 - sim | 2 - dontcare
	char sigilo;//1 - reservado | 2 - secreto | 3 - ultrasecreto
	string social;//se for recebida recebe o rementente, se for enviada recebe o destinatario
	string socialpais;//se for recebida recebe o pais rementente, se for enviada recebe o pais destinatario
}Mensagem;

typedef struct{
	string sigla;
	string pais;
	char rep;//0 - embaixada | 1 - consulado
	string senha;
	Mensagem m[500];
	int total;
}Diplomata;

int main(){
	
	int cadastros = 0, i, j, contador, auxint;
	float a, b, c;
	bool flag, login, token;
	char opcao, subopcao, auxmenu, menudomenu, auxchar, auxsigilo, paradados;
	string senhamestra, aux, auxigla, auxenha, auxassunto, auxmensagem;
	Diplomata dip[25];
	time_t rawtime;
	struct tm *timeinfo;
	
	senhamestra = "12345";//senha padrao
		
	while(1){
		system("cls");
		cout << "1)Administracao de representacoes consulares\n";
		cout << "2)Consulta e transmissao de mensagem\n";
		cout << "3)Fechar programa\n";
		cout << "Opcao: ";
		cin >> opcao;
		
		if(opcao == '1'){
			fflush_stdin();
			subopcao = '0';
			system("cls");
			cout << "Senha administrativa: ";
			getline(cin, auxenha);
			if(auxenha == senhamestra){
				while(subopcao != '4'){
					system("cls");
					cout << "1)Cadastrar nova representacao\n";
					cout << "2)Listagem de representacoes cadastradas\n";
					cout << "3)Relatorios\n";
					cout << "4)Voltar ao menu inicial\n";
					cout << "5)Encerrar o programa\n";
					cout << "Opcao: ";
					cin >> subopcao;
					fflush_stdin();
					if(subopcao == '1'){
						if(cadastros == 25){
							cout << "Limite maximo de cadastrados\n";
							system("pause");
							break;
						}
						system("cls");
						flag = false;
						contador = 0;
						while(!flag){
							cout << "Sigla de identificacao unica: ";
							getline(cin, aux);
							for(i = 0; i < cadastros; i++){
								if(dip[i].sigla != aux){
									contador++;
								}
							}
							if(contador != cadastros){
								flag = false;
								cout << "Sigla ja existe!\n";
							}
							else{
								dip[cadastros].sigla = aux;
								flag = true;
								cout << "Senha para acesso: ";
								getline(cin, aux);
								dip[cadastros].senha = aux;
								cout << "Pais que se encontra sediado a representacao: ";
								getline(cin, dip[cadastros].pais);
								cout << "Nivel de representacao (0 - embaixada | 1 - consulado): ";
								cin >> auxchar;
								if((auxchar == '0') || (auxchar == '1')){
									dip[cadastros].rep = auxchar;
									dip[i].total = 0;
									cadastros++;
									cout << "Cadastrado com sucesso!\n";
									system("pause");
								}
								else{
									flag = false;
									cout << "Dado inserido invalido, tente cadastrar novamente!";
									system("pause");
									break;
								}
							}
						}

					}
					if(subopcao == '2'){
						system("cls");
						for(i = 0; i < cadastros; i++){
							cout << "Sigla: " << dip[i].sigla << "\n";
							cout << "Pais que esta localizado: " << dip[i].pais << "\n";
							cout << "____________________________________________________________\n";
						}
						system("pause");
					}
					if(subopcao == '3'){
						paradados = '5';
						while(paradados != '4'){
							system("cls");
							cout << "1)Quantitativo de mensagens enviadas por cada representacao diplomatica\n";
							cout << "2)Quantitativo de mensagens recebidas por cada representacao diplomatica\n";
							cout << "3)Percentual de mensagens transmitidas por grau de sigilo\n";
							cout << "4)Voltar ao menu inicial\n";
							cout << "Opcao: ";
							cin >> paradados;
							if(paradados == '1'){
								system("cls");
								for(i = 0; i < cadastros; i++){
									a = 0;
									for(j = 0; j < dip[i].total; j++){
										if(dip[i].m[j].tipo){
											a++;
										}
									}
									cout << "Representacao diplomatica: " << dip[i].sigla << "\n";
									cout << "Quantidade de mensagens enviadas: " << a << "\n";
									cout << "____________________________________________________________\n";
								}
								system("pause");
							}
							if(paradados == '2'){
								system("cls");
								for(i = 0; i < cadastros; i++){
									a = 0;
									for(j = 0; j < dip[i].total; j++){
										if(!dip[i].m[j].tipo){
											a++;
										}
									}
									cout << "Representacao diplomatica: " << dip[i].sigla << "\n";
									cout << "Quantidade de mensagens recebidos: " << a << "\n";
									cout << "____________________________________________________________\n";
								}
								system("pause");
							}
							if(paradados == '3'){
								system("cls");
								a = 0;
								b = 0;
								c = 0;
								for(i = 0; i < cadastros; i++){
									for(j = 0; j < dip[i].total; j++){
										if(dip[i].m[j].sigilo == '1'){
											a++;
										}
										if(dip[i].m[j].sigilo == '2'){
											b++;
										}
										if(dip[i].m[j].sigilo == '3'){
											c++;
										}
									}
								}
								cout << "Reservado: " << (a * (100/(a + b + c))) << "%\n";
								cout << "Secreto: " << (b * (100/(a + b + c))) << "%\n";
								cout << "Ultrassecreto: " << (c * (100/(a + b + c))) << "%\n";
								system("pause");
							}
						}
					}
					if(subopcao == '5'){
						return 0;
					}
				}
			}	
		}
		
		if(opcao == '2'){
			fflush_stdin();
			system("cls");
			login = false;
			menudomenu = '7';
			while(!login){
				cout << "Sigla de identificacao: ";
				getline(cin, auxigla);
				for(i = 0; i < cadastros; i++){
					if(dip[i].sigla == auxigla){
						cout << "Senha de acesso: ";
						getline(cin, auxenha);
						if(dip[i].senha == auxenha){
							login = true;
							system("cls");
							while(menudomenu != '5'){
								system("cls");
								cout << "1)Listagem de mensagens recebidas\n";
								cout << "2)Leitura de mensagens recebidas\n";
								cout << "3)Enviar mensgem\n";
								cout << "4)Lista de mensagens enviadas\n";
								cout << "5)Voltar ao menu inicial\n";
								cout << "6)Encerrar programa\n";
								cout << "Opcao: ";
								cin >> menudomenu;
								if(menudomenu == '1'){
									system("cls");
									for(j = 0; j < dip[i].total; j++){	
										if(!dip[i].m[j].tipo){
											cout << "Ordem: " << dip[i].m[j].ordem << "\n";
											cout << "Rementente: " << dip[i].m[j].social<< "\n";
											cout << "Assunto: " << dip[i].m[j].assunto << "\n";
											cout << "Hora: " << dip[i].m[j].h[0] << ":" << dip[i].m[j].h[1] << ":" << dip[i].m[j].h[2] << "\n";
											if(dip[i].m[j].vizualizada == 1){
												cout << "Vizualizada\n";
											}
											else{
												cout << "Nao vizualizada\n";
											}
											cout << "____________________________________________________________\n";
										}
									}
									system("pause");
								}
								if(menudomenu == '2'){
									system("cls");
									cout << "Insira o numero de ordem da mensagem: ";
									cin >> auxint;
									flag = false;
									fflush_stdin();
									for(j = 0; j < dip[i].total; j++){
										if((dip[i].m[j].ordem == auxint) && (!dip[i].m[j].tipo)){
											cout << "Rementente: " << dip[i].m[j].social << "\n";
											cout << "Localizacao: " << dip[i].m[j].socialpais << "\n";
											cout << "Assunto: " << dip[i].m[j].assunto << "\n";
											cout << "Hora: " << dip[i].m[j].h[0] << ":" << dip[i].m[j].h[1] << ":" << dip[i].m[j].h[2] << "\n";
											cout << "Mensagem:\n";
											cout << dip[i].m[j].mensagem << "\n";
											cout << "------------------------------------------------------------\n";
											dip[i].m[j].vizualizada = 1;
											flag = true;
										}
									}
									if(!flag){
										cout << "O numero digitado nao esta associado a nenhuma mensagem!\n";
									}
									system("pause");								
								}
								if(menudomenu == '3'){
									fflush_stdin();
									system("cls");
									cout << "Sigla da representacao diplomatica destino: ";
									getline(cin, auxigla);
									token = false;
									for(j = 0; j < cadastros; j++){
										if((dip[j].sigla == auxigla) && (dip[i].sigla != auxigla)){
											token = true;
											cout << "Assunto da mensagem (com ate 50 caracteres): ";
											getline(cin, auxassunto);
											if(auxassunto.length() <= 50){
												cout << "Mensagem: ";
												getline(cin, auxmensagem);
												if(auxmensagem.length() <= 500){
													cout << "Grau de sigilo (1 - reservado | 2 - secreto | 3 - ultrassecreto): ";
													cin >> auxsigilo;
													if((auxsigilo == '1') || (auxsigilo == '2') || (auxsigilo == '3')){
														fflush_stdin();
														cout << "Insira a sua senha para confirmar o envio: ";
														getline(cin, auxenha);
														if(dip[i].senha == auxenha){
															rawtime = time(NULL);
															timeinfo = localtime(&rawtime);
															dip[j].m[dip[j].total].social = dip[i].sigla;
															dip[j].m[dip[j].total].socialpais = dip[i].pais;
															dip[j].m[dip[j].total].assunto = auxassunto;
															dip[j].m[dip[j].total].mensagem = auxmensagem;
															dip[j].m[dip[j].total].sigilo = auxsigilo;	
															dip[j].m[dip[j].total].h[0] = timeinfo->tm_hour;
															dip[j].m[dip[j].total].h[1] = timeinfo->tm_min;
															dip[j].m[dip[j].total].h[2] = timeinfo->tm_sec;
															dip[j].m[dip[j].total].tipo = false;
															dip[j].m[dip[j].total].vizualizada = 0;
															if(dip[j].total == 0){
																dip[j].m[dip[j].total].ordem = 1;
															}
															else{
																dip[j].m[dip[j].total].ordem = dip[j].m[dip[j].total - 1].ordem + 1;
															}
															dip[j].total++;
															dip[i].m[dip[i].total].social = dip[j].sigla;
															dip[i].m[dip[i].total].socialpais = dip[j].pais;
															dip[i].m[dip[i].total].assunto = auxassunto;
															dip[i].m[dip[i].total].mensagem = auxmensagem;
															dip[i].m[dip[i].total].sigilo = auxsigilo;
															dip[i].m[dip[i].total].h[0] = timeinfo->tm_hour;
															dip[i].m[dip[i].total].h[1] = timeinfo->tm_min;
															dip[i].m[dip[i].total].h[2] = timeinfo->tm_sec;
															dip[i].m[dip[i].total].tipo = true;
															dip[i].m[dip[i].total].vizualizada = 2;
															dip[i].total++;															
														}
														else{
															cout << "Senha incorreta, tente enviar uma nova mensagem!\n";
															system("pause");
															break;
														}
													}
													else{
														cout << "Indice incorreto, tente enviar uma nova mensagem!\n";
														system("pause");
														break;
													}
												}
												else{
													cout << "Texto muito grande, tente enviar uma nova mensagem!\n";
													system("pause");
													break;
												}
											}
											else{
												cout << "Assunto muito grande, tente enviar uma nova mensagem!\n";
												system("pause");
												break;
											}
										}
									}
									if(!token){
										cout << "Sigla destino invalida, inicie o processo de envio novamente!\n";
										system("pause");
									}
								}
								if(menudomenu == '4'){
									system("cls");
									for(j = 0; j < dip[i].total; j++){	
										if(dip[i].m[j].tipo){
											cout << "Rementente: " << dip[i].m[j].social<< "\n";
											cout << "Assunto: " << dip[i].m[j].assunto << "\n";
											cout << "Hora: " << dip[i].m[j].h[0] << ":" << dip[i].m[j].h[1] << ":" << dip[i].m[j].h[2] << "\n";
											cout << "____________________________________________________________\n";
										}
									}
									system("pause");
								}
								if(menudomenu == '6'){
									return 0;
								}
							}
						}
					}
				}
				if(!login){
					cout << "Sigla ou senha incorreta, insira qualquer tecla para tentar novamente ou 1 para voltar ao menu principal\n";
					cin >> auxmenu;
					fflush_stdin();
					if(auxmenu == '1'){
						break;
					}
					system("cls");
				}
			}		
		}
		if(opcao == '3'){
			return 0;
		}
	}
}
