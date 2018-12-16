#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535

/* Dimenzije prozora */
static int window_width, window_height;

/* Ugao rotacije kamere */
float ro;

static void initialize(void){
    
    glClearColor(0.5, 0.5, 0.5, 0);
    glEnable(GL_DEPTH_TEST);
    
}

static void on_display(void){
    
    /* Brisanje prehodnog sadrzaja prozora */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Podesavanje viewport-a */
    glViewport(0, 0, window_width, window_height);
    
    /* Podesavanje projekcije */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/(float)window_height, 1, 25);
    
    /* Podesavanje vidne tacke */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(sqrt(2)*15/5*sin(ro), sqrt(2)*15/5*cos(ro), 30/5, 0, 0, 0, 0, 0, 1);
    
    /* Pravougaonik sa kalupima */
    glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glVertex3f(5, 5, 0);
        glVertex3f(5, -5, 0);
        glVertex3f(-5, -5, 0);
        glVertex3f(-5, 5, 0);
    glEnd();

    /* Pomocne linije */
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(10,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);
        
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
    glEnd();
    
    /* Postavljanje offset-a tako da se manji objekat bolje vidi */
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0, 1.0);
    
    /* Pravljenje kalupa u obliku kvadrata */
    glBegin(GL_POLYGON);
        glColor3f(0, 0, 0);
        glVertex3f(3, 3, 0);
        glVertex3f(3, 1, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(1, 3, 0);
    glEnd();
    
    /* Iskljucivanje offset-a */
    glDisable(GL_POLYGON_OFFSET_FILL);
    
    /* Nova slika se salje na ekran */
    glutSwapBuffers();
    
}

static void on_keyboard(unsigned char key, int x, int y){
    
    switch(key){
    
        /* Ako korisnik pritisne Esc program se zavrsava */
        case 27:
            exit(0);
            break;
            
        /* Pritiskom tastera q kamera se pomera ulevo */
        case 'q':
            ro = ro + 0.1;
            if (ro >= 2*(PI)){
                ro = ro - 2*(PI);
            }
            glutPostRedisplay();
            break;
            
        /* Pritiskom tastera e kamera se pomera udesno */
        case 'e':
            ro = ro - 0.1;
            if (ro < 0){
                ro = ro + 2*(PI);
            }
            glutPostRedisplay();
            break;
    }
    
}

static void on_reshape(int width, int height){
    
    /* Azuriranje sirine i visine prozora */
    window_width = width;
    window_height = height;
    
}

int main(int argc, char** argv){
    
    /* Inicijalizacija GLUT-a */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    /* Kreiranje prozora */
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("The Game");
    
    /* Registrovanje callback funkcija */
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    
    /* Obavljanje OpenGL inicijalizacije */
    initialize();
    
    /* Postavljanje pocetnog ugla */
    ro = (PI)/4;
    
    /* Ulazak u glavnu petlju */
    glutMainLoop();
    
    return 0;
    
}












