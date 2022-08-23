/*Versão beta desenvolvida por Thiago Felski Pereira para disciplina de Algoritmos*/
#include <iostream> // Para conseguir usar inputs e outputs no terminal
#include <windows.h> // Comandos para rodar o programa no Windows
#include <conio.h> /// Para usar o getch() no Windows
#include <time.h> // Habilita a função time
///https://stackoverflow.com/questions/34474627/linux-equivalent-for-conio-h-getch

using namespace std;

/* Mateus Barbosa, Matheus Rocha, Victor André Uller, Leonardo Beduschi Iunes, */

/**
    F L A P B I R D (M2 Algoritmos)
    - Lembrando: não permitido o uso de funções e variaveis compostas como structs, vetores e matrizes
    - Corrigir os rastros (pássaro e obstáculos) - OK
    - Implementar colisão  - OK
    - Implementar pontuação (mais um ponto para cada obstáculo superado) - OK
    - Fazer 2 obstáculos simultaneos (obstaculo1 e obstaculo2) - OK
    - Deixar a pontuação visível durante todo o jogo - OK
    - Definir marcos para acelerar a velocidade - OK
*/

int main() {
    ///ALERTA: NÃO MODIFICAR O TRECHO DE CÓDIGO, A SEGUIR.
    //INICIO: COMANDOS PARA QUE O CURSOR NÃO FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    //FIM: COMANDOS PARA QUE O CURSOR NãO FIQUE PISCANDO NA TELA
    //INÍCIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
    COORD coord;
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INÍCIO DA TELA
    ///ALERTA: NãO MODIFICAR O TRECHO DE CÓDIGO, ACIMA.

    srand(time(NULL)); // Obrigatório para conseguir gerar um valor aleatório a cada momento. E para poder usar o rand()
     
    // Inicialização de variáveis
    int bird_x = 5, bird_y = 6, bird_y_old_position;
    int obstaculo_x = 110, obstaculo_y, obstaculo_x_old_position;
    int obstaculo2_x = obstaculo_x + 55, obstaculo2_y, obstaculo2_x_old_position;

    int tecla; // Para conseguir checar qual tecla o usuário pressionou
    int placar = 0; // Highscore do usuário
    int placar_x = 50, placar_y = 22; // Localização do placar
    int tamanho_passagem_1 = rand() % 20; // Gera valores aleatórios de 0 ao 19 para o obstaculo1
    int tamanho_passagem_2 = rand() % 20+1; // Gera valores aleatórios de 0 ao 19 para o obstaculo2
    float velocidade = 150; // Velocidade em que o jogo esta no momento

    bool playing = false; // Determina se o jogo está rodando ou não

    system("cls"); // Usado para limpar o terminal, evitando assim qualquer distorção no layout

    // Desenho do cenário
    cout<<"-----------------------------------------------------------------------------------------------------";
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<<"-----------------------------------------------------------------------------------------------------";

    // Menu inicial
    coord.X = 40; coord.Y = 10; // Seta uma coordenada X e Y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Seleciona o ponto da coordenada informada. Com o ponto de origem sendo o canto superior esquerdo do CMD
    cout << "Bem-vindo ao FlappyBird!"; // Coloca um item na cordenada selecionada
    // (Passos Anteriores se repetem para todos os items que envolvem coordenadas)
    coord.X = 40; coord.Y = 11;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "Aperte W para comecar a jogar";
    coord.X = 40; coord.Y = 12;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "Q (Sair do Jogo)";

    tecla = getch(); // Espera por um input do usuário

    // Valida a tecla (Maiúscula ou Minúscula) apertada no menu inicial
    switch(tecla) {
        case 'w': case 'W':
            system("cls");

            ///Desenho Do cenario
            cout<<"-----------------------------------------------------------------------------------------------------";
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout<<"-----------------------------------------------------------------------------------------------------";

            // Inicia o jogo
            playing = true;

            // Lógica para fazer o jogo funcionar
            do {
                // Poscicionamento do placar
                coord.X = placar_x; coord.Y = placar_y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout << "PLACAR: " << placar;
                
                // Apaga os rastros do pássaro
                coord.X = bird_x;    
                coord.Y = bird_y_old_position;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<" ";

                // Posiciona o pássaro
                coord.Y = bird_y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                cout<<char(190);

                // Armazena a última posição do pássaro
                bird_y_old_position = bird_y;

                // Posiciona o obstáculo
                obstaculo_y=1;
                obstaculo2_y=1;
                while(obstaculo_y < 20 && obstaculo2_y < 20){
                    // Remove o rastro do obstáculo1
                    coord.X = obstaculo_x_old_position;    coord.Y = obstaculo_y;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    cout<<" ";

                    // Remove o rastro do obstáculo2
                    coord.X = obstaculo2_x_old_position;    coord.Y = obstaculo2_y;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    cout<<" ";

                    // Define a posição e tamanho da passagem para o pássaro
                    coord.X = obstaculo_x;    coord.Y = obstaculo_y;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    
                    // Define a parte do obstáculo que o pássaro NÃO pode passar
                    if(obstaculo_y < tamanho_passagem_1 - 1 || obstaculo_y > tamanho_passagem_1 + 1) {
                        cout<<char(219);
                    } else {
                        // Define a passagem do obstáculo que o pássaro pode passar
                        cout<<" ";
                    }
                    obstaculo_y++;

                    // Só mostra o obstáculo2 após ele chegar a parte inicial da tela, para evitar bugs no layout e ter consistencia no espaço entre os obstáculos
                    if(obstaculo2_x < 110) {
                        // Posiciona Obstáculo 2
                        coord.X = obstaculo2_x;    coord.Y = obstaculo2_y;
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        if(obstaculo2_y < tamanho_passagem_2 - 1 || obstaculo2_y > tamanho_passagem_2 + 1) {
                            cout<<char(219);
                        } else {
                            cout<<" ";
                        }
                    }
                    obstaculo2_y++;
                }

                // Valida se a coordenada X do passáro é a mesma da coordanada X do obstáculo1
                // E se a coordenada Y do pássaro é diferente da coordenada da passagem do obstáculo
                if(bird_x == obstaculo_x && (bird_y < tamanho_passagem_1 - 1 || bird_y > tamanho_passagem_1 + 1)) {
                    playing = false;
                } else if(bird_x == obstaculo2_x && (bird_y < tamanho_passagem_2 - 1 || bird_y > tamanho_passagem_2 + 1)) { // Verifica a colisão com obstaculo 2, seguindo os mesmos items do obstáculo1
                    playing = false;
                }
                
                if (kbhit()) { // Verifica se uma tecla foi pressionada
                    tecla=getch(); // Verifica comando do jogador
                }
                
                if (tecla == 'w'){
                    // Pássaro sobe 1 posição ao precionar a tecla W
                    bird_y--;
                    // Reseta a tecla para que ela não fique "precionada"
                    tecla='0';
                } else {
                    // Pássaro cai 1 posição se não for pressionado para subir
                    bird_y++;
                }

                // Valida a colisão com as bordas da tela
                if(bird_y > 20 || bird_y < 0) {
                    playing = false;
                }

                // Armazena a última posição no eixo X do obstáculo1 e obstáculo2
                obstaculo_x_old_position = obstaculo_x;
                obstaculo2_x_old_position = obstaculo2_x;

                //  Obstáculo1 e Obstáculo2 avança uma posição para esquerda
                obstaculo_x--;
                obstaculo2_x--;

                // Velocidade atual do jogo
                Sleep(velocidade);
                
                // Adiciona pontuação ao placar quando passar por um obstáculo  
                if (bird_x == obstaculo_x + 1 or bird_x == obstaculo2_x + 1) {
                    placar++; // Adiciona +1 ao placar
                    if (placar != 0 && placar % 5 == 0) {
                        // Se o valor da pontuação for diferente de zero e ser multiplo de cinco
                        // a velocidade aumenta a cada cinco obstaculos passados
                        velocidade = velocidade - 25; // Aumenta a velocidade do jogo por 25 segundos
                    }
                }
            
                // Retona obstáculo para a posição inicial e randomiza a passagem para o pássaro
                if(obstaculo_x < 0) {
                    obstaculo_x = 110;
                    tamanho_passagem_1 = rand() % 20;
                } else if(obstaculo2_x < 0) {
                    obstaculo2_x = 110;
                    tamanho_passagem_2 = rand() % 20;
                }

                if(!playing) {
                    // Tela de Game Over
                    coord.X = 40; coord.Y = 10;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    cout << "Sua pontuacao final: " << placar;

                    coord.X = 40; coord.Y = 11;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    cout << "Deseja jogar novamente? (S) ou (N)";

                    tecla = getch(); // Espera por um input do usuário
                    switch(tecla) {
                        case 's': case 'S':
                        // Reseta o jogo. Declarando os valores das variáveis ao seu estado inicial
                            tecla = '0';
                            system("cls");

                            cout<<"-----------------------------------------------------------------------------------------------------";
                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                            cout<<"-----------------------------------------------------------------------------------------------------";

                            bird_y = 6;

                            obstaculo_x = 110;
                            tamanho_passagem_1 = rand() % 20;

                            obstaculo2_x = obstaculo_x + 30;
                            tamanho_passagem_2 = rand() % 20;

                            placar = 0;

                            playing = true;
                            break;
                        case 'n': case 'N':
                        // Sai do jogo
                            system("cls");
                            system("exit");
                            break;
                    }
                }
            } while (playing);
            break;
        // Sai do jogo
        case 'q': case 'Q':
            system("cls");
            system("exit");
            return 0;
            break;
    }
}
