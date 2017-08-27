#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "CarregarArquivo.cpp"

void PosicionaObservador(void);
void EspecificaParametrosVisualizacao(void);

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;
CarregarArquivo Carro;
CarregarArquivo Pista;
int desenho = 1;
float r,g,b;
GLint especMaterial = 60;
using namespace std;

class Movimento
{
public:
    float tx,ty,tz,rodar_x,rodar_y,rodar_z;
    Movimento()
    {
        tx = ty = tz = rodar_x = rodar_y = rodar_z = 0.0;

    }
    void set_movimento(float tx1,float ty1,float tz1,float rodar_x1,float rodar_y1,float rodar_z1)
    {
        tx = tx1;
        ty = ty1;
        tz = tz1;
        rodar_x = rodar_x1;
        rodar_y = rodar_y1;
        rodar_z = rodar_z1;

    }
};

Movimento carro;


void DefineIluminacao (void)
{
    GLfloat luzAmbiente[4]= {0.2,0.2,0.2,1.0};
    GLfloat luzDifusa[4]= {0.7,0.7,0.7,1.0}; // "cor"
    GLfloat luzEspecular[4]= {r, g, b, 1.0}; // "brilho"
    GLfloat posicaoLuz[4]= {0.0, 150.0, 150.0, 1.0};
    GLfloat posicaoLuz2[4]= {0, 100.0, 80.0, 1.0};
    // Capacidade de brilho do material
    GLfloat especularidade[4]= {1.0,1.0,1.0,1.0};
    // Define a refletância do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    // Define os parâmetros da luz de número 1
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    //glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
    glEnable(GL_LIGHT0);
    // Define os parÃ¢metros da luz de nÃºmero 2
    glLightfv(GL_LIGHT2, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT2, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuz2 );
    glEnable(GL_LIGHT2);
}


// Função callback chamada para fazer o desenho
void Desenha(void)
{
    // Limpa a janela de visualização com a cor
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Troca cor corrente para azul
    glColor3f(1.0f, 0.0f, 0.0f);
    DefineIluminacao();

    if(desenho == 1){
        glPushMatrix();
        // Desenha um aviao

        glScalef( 10.0, 10.0, 10.0);

        for ( int j = 0; j < (Carro.faces).size(); ++j )
        {

            glBegin ( GL_POLYGON );

            for (int i = 0; i < (Carro.faces[j]).size() ; ++i )
            {
                GLfloat nor[3] = {(Carro.normais[Carro.faces[j][i][2]][0]),(Carro.normais[Carro.faces[j][i][2]][1]),(Carro.normais[Carro.faces[j][i][2]][2])};
                glNormal3fv(nor);
                GLfloat vert[3] = {(Carro.vertices1[Carro.faces[j][i][0]][0]),(Carro.vertices1[Carro.faces[j][i][0]][1]),(Carro.vertices1[Carro.faces[j][i][0]][2])};
                glVertex3fv (vert);

            }

            glEnd( );
        }
        glColor3f(0.5f, 0.5f, 0.5f);

        for ( int j = 0; j < (Pista.faces).size(); ++j )
        {

            glBegin ( GL_POLYGON );

            for (int i = 0; i < (Pista.faces[j]).size() ; ++i )
            {
                GLfloat nor[3] = {(Pista.normais[Pista.faces[j][i][2]][0]),(Pista.normais[Pista.faces[j][i][2]][1]),(Pista.normais[Pista.faces[j][i][2]][2])};
                glNormal3fv(nor);
                GLfloat vert[3] = {(Pista.vertices1[Pista.faces[j][i][0]][0]),(Pista.vertices1[Pista.faces[j][i][0]][1]),(Pista.vertices1[Pista.faces[j][i][0]][2])};
                glVertex3fv (vert);

            }

            glEnd( );
        }
    }else if(desenho == 2){
        glutSolidTeapot(6);
    }



    glPopMatrix();


    // Execução dos comandos de desenho
    glutSwapBuffers();
}


// Inicialização
void Inicializa(void)
{
    r, g , b =1.0;
    Carro.Carregar("carro.obj");//carrega o arquivo
    Pista.Carregar("pista.obj");//carrega o arquivo
    // Define a cor de fundo da janela de visualização como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial (GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE );
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);// normaliza as normais
    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);
    // Inicializa a variável que especifica o ângulo da projeção
    // perspectiva
    angle=50;
    // Inicializa as variáveis usadas para alterar a posição do
    // observador virtual
    rotX = 0;
    rotY = 0;
    EspecificaParametrosVisualizacao();
}


// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    DefineIluminacao();
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    gluLookAt(0,0,180,0,0,0,0,1,0);
    // Especifica posição do observador e do alvo
    glRotatef(rotX,1,0,0);
    glRotatef(rotY,0,1,0);
}


// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(angle,fAspect,0.5,500);

    PosicionaObservador();
}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica as dimensões da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}


// Callback para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
        {
            // Zoom-in
            if (angle >= 10)
                angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN)
        {
            // Zoom-out
            if (angle <= 130)
                angle += 5;
        }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}


// Função callback chamada para gerenciar eventos de teclas especiais (F1,PgDn,...)
void TeclasEspeciais (int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_LEFT:
        rotY--;
        break;
    case GLUT_KEY_RIGHT:
        rotY++;
        break;
    case GLUT_KEY_UP:
        rotX++;
        break;
    case GLUT_KEY_DOWN:
        rotX--;
        break;
    case GLUT_KEY_HOME:
        obsZ++;
        break;
    case GLUT_KEY_END:
        obsZ--;
        break;
    case GLUT_KEY_F1:
        if (especMaterial < 100){
            especMaterial = especMaterial + 5;
            cout << "EspecMaterial " << especMaterial << "\n";
        }
        if (especMaterial == 100){
            especMaterial = 100;
            cout << "EspecMaterial " << especMaterial << "\n";
        }
        break;
    case GLUT_KEY_F2:
        if (especMaterial > 10){
            especMaterial = especMaterial - 5;
            cout << "EspecMaterial " << especMaterial << "\n";
        }
        if (especMaterial == 10){
            especMaterial = 10;
            cout << "EspecMaterial " << especMaterial << "\n";
        }
        break;
    }
    PosicionaObservador();
    glutPostRedisplay();
}

void Timer(int value)
{
    if(value > 0)
    {
        value--;
        glutTimerFunc(200,Timer,value);
        glutPostRedisplay();
    }
}

void Teclado(unsigned char key, int x, int y)
{

    if(key == 'w')
    {
        carro.tx = carro.tx + 0.5;
        //glutTimerFunc(200,Timer,Perna.num_quadros);

    }
    if(key == 's')
    {
        carro.tx = carro.tx - 0.5;
        //glutTimerFunc(200,Timer,Perna.num_quadros);

    }
    if(key == 'a')
        glShadeModel(GL_SMOOTH);
    if(key == 'd')
        glShadeModel(GL_FLAT);
    if(key == 'c')
        desenho = 1;
    if(key == 'x')
        desenho = 2;
    if(key == '+')
    {
        if (r >= 1.0 || g >= 1.0 || b >= 1.0){
            cout << "R, G, B = 1.0/ \n";
            r = 1.0;
            g = 1.0;
            b = 1.0;
        }
        else{
            r = r  + 0.1;
            g = g  + 0.1;
            b = b  + 0.1;
            cout << "R, G, B = " << r << "\n";
        }
    }
    if(key == '-')
    {
        if (r == 0.0 || g == 0.0 || b == 0.0){
            r = 0.0;
            g = 0.0;
            b = 0.0;
            cout << "R, G, B = 0.0/ \n";
        }
        else if (r > 0.0 && r <= 1.0 || g > 0.0 && g <= 1.0 || b > 0.0 && b <= 1.0){
            r = r  - 0.1;
            g = g  - 0.1;
            b = b  - 0.1;
            cout << "R, G, B = " << r << "\n";
        }
    }



    glutPostRedisplay();

}

// Programa Principal
int main()
{
    int argc = 0;
    char *argv[] = { (char *)"gl", 0 };

    glutInit(&argc,argv);

    // Define do modo de operacao da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Especifica a posição inicial da janela GLUT
    glutInitWindowPosition(5,5);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(800,800);

    // Cria a janela passando como argumento o titulo da mesma
    glutCreateWindow("Desenho de um objeto com iluminação");

    // Registra a funcao callback de redesenho da janela de visualizacao
    glutDisplayFunc(Desenha);
    // Registra a funcao callback para tratamento das teclas especiais
    glutSpecialFunc(TeclasEspeciais);
    // Registra a funcao callback para tratamento do redimensionamento da janela
    glutReshapeFunc(AlteraTamanhoJanela);
    // Registra a funcao callback para tratamento do mouse
    glutMouseFunc(GerenciaMouse);
    glutKeyboardFunc(Teclado);

    Inicializa();
    glutMainLoop();
}
