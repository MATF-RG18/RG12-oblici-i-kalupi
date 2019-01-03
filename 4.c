#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PI 3.1415926535

/* Dimenzije prozora */
static int window_width, window_height;

/* Ugao rotacije kamere */
float ro, phi;

/* Ugao i smer pozicije svetlosti */
float beta;
int smer_pozicije_svetlosti;

/* Pomeraj tela po svakoj osi*/
float pomeraj_po_x, pomeraj_po_y, pomeraj_po_z;

/* Rotacija tela po z osi */
float rotacija_tela = 0;

/* Koordinate centra kalupa */
float centar_rupe[2];
float centar_rupe2[2];
float centar_rupe3[2];
float centar_rupe4[2];

/* Izabrani oblik */
int oblik;

/* Pravi se random objekat */
void novi_objekat(void){
    srand(time(NULL)); 
    oblik = rand()%4+1;    
    rotacija_tela = (float)(rand()%20)*18;
}

static void initialize(void){
    
    glClearColor(0.5, 0.5, 0.5, 0);
    glEnable(GL_DEPTH_TEST);
    
}

static void on_timer(int value)
{
    /* Proveravanje da li smo usli iz zeljene callback funkcije */
    if (value != 0)
        return;
    
    /* Odredjivanje u kom smeru treba da se krece pozicija svetlosti i pomeranje ugla te pozicije */
    if (smer_pozicije_svetlosti == 1){
        beta += 0.01*(PI);
        if(beta >= (PI)/4){
            smer_pozicije_svetlosti = 0;
        }
    }
    else {
        beta -= 0.01*(PI);
        if(beta <= -(PI)/4){
            smer_pozicije_svetlosti = 1;
        }
    }
    
    /* Pozivanje display funkcije */
    glutPostRedisplay();

    /* Ponovno pozivanje tajmera */
    glutTimerFunc(100, on_timer, 0);
}

static void on_display(void){
    
    /* Promenljive koje cuvaju informacije o svetlosti i materijalima */
    /* Pozicija svetlosti se menja u odnosu na ugao koji se menja u tajmeru */
    GLfloat pozicija_svetla[] = { 0, 7*sin(beta), 7*cos(beta), 1 };
    GLfloat ambijent_svetla[] = { 0.1, 0.0, 0.0, 1 };
    GLfloat difuznost_svetla[] = { 1, 0.9, 0.9, 1 };
    GLfloat spekularnost_svetla[] = { 1, 0.9, 0.9, 1 }; 
    GLfloat ambijent_materijala_pravougaonika[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat difuznost_materijala_pravougaonika[] = { 0.1, 0.0, 0.0, 1 };
    GLfloat spekularnost_materijala_pravougaonika[] = { 1, 1, 1, 1 };
    GLfloat osvetljenje_pravougaonika = 10;
    GLfloat ambijent_materijala_kalupa[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat difuznost_materijala_kalupa[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat spekularnost_materijala_kalupa[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat osvetljenje_kalupa = 50;
    GLfloat ambijent_materijala_oblika[] = { 0.4, 0.1, 0.1, 1 };
    GLfloat difuznost_materijala_oblika[] = { 0.5, 0.1, 0.3, 1 };
    GLfloat spekularnost_materijala_oblika[] = { 0.8, 0.7, 0.8, 1 };
    GLfloat osvetljenje_oblika = 100;
    
    /* Brisanje prehodnog sadrzaja prozora */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Podesavanje viewport-a */
    glViewport(0, 0, window_width, window_height);
    
    /* Podesavanje projekcije */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/(float)window_height, 1, 25);
    
    /* Dozvoljava se upotreba svetlosti */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    /* Podesavanje vidne tacke */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.5*2*3*cos(ro)*sin(phi), 1.5*2*3*sin(ro)*sin(phi), 1.5*sqrt(2)*6*cos(phi), 0, 0, 0, 0, 0, 1);
    
    /* Postavljanje svetlosti i materijala za pravougaonik */
    glLightfv(GL_LIGHT0, GL_POSITION, pozicija_svetla);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambijent_svetla);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difuznost_svetla);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spekularnost_svetla);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambijent_materijala_pravougaonika);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuznost_materijala_pravougaonika);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spekularnost_materijala_pravougaonika);
    glMaterialf(GL_FRONT, GL_SHININESS, osvetljenje_pravougaonika);
    
    /* Pravougaonik sa kalupima */
    glBegin(GL_POLYGON);
       /* glColor3f(1, 1, 1);*/
        glNormal3f(0,0,1);
        glVertex3f(5, 5, 0);
        glVertex3f(5, -5, 0);
        glVertex3f(-5, -5, 0);
        glVertex3f(-5, 5, 0);
    glEnd();

    /* Pomocne linije */
 /*   glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(10,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);
        
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
    glEnd();*/
 
    
    /* Postavljanje offset-a tako da se manji objekat bolje vidi */
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0, 1.0);
    
    /* Postavljanje materijala za kalupe */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambijent_materijala_kalupa);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuznost_materijala_kalupa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spekularnost_materijala_kalupa);
    glMaterialf(GL_FRONT, GL_SHININESS, osvetljenje_kalupa);
    
    /* Pravljenje kalupa u obliku kvadrata */
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        /*glColor3f(0, 0, 0);*/
        glVertex3f(3, 3, 0);
        glVertex3f(3, 2, 0);
        glVertex3f(2, 2, 0);
        glVertex3f(2, 3, 0);
    glEnd();
    
    /* Pravljenje kalupa u obliku kruga */
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0,0,1);
        /*glColor3f(0, 0, 0);*/
        glVertex3f(-2, 2, 0);
        float alpha;
        for(alpha = 0; alpha < 2*(PI) + 0.1; alpha += 0.1){
            glVertex3f(-2 + cos(alpha)*0.6, 2 + sin(alpha)*0.6, 0);
        }
    glEnd();
    
    /* Pravljenje kalupa za valjak */
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        /*glColor3f(0, 0, 0);*/
        glVertex3f(-1, -1, 0);
        glVertex3f(-1, -2.4, 0);
        glVertex3f(-1.8, -2.4, 0);
        glVertex3f(-1.8, -1, 0);
    glEnd();
    
    /* Pravljenje kalupa za zvezdu */
    int i;
    float u;
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        /*glColor3f(0, 0, 0);*/
        for(i = 0, u = 0; u < 2*(PI); i++, u+= 0.2*(PI)){
            if(i%2==0)
                glVertex3f(3+0.35*cos(u), -2+0.35*sin(u), 0);
            else
                glVertex3f(3+0.7*cos(u), -2+0.7*sin(u), 0);
        }
    glEnd();
    

    /* Iskljucivanje offset-a */
    glDisable(GL_POLYGON_OFFSET_FILL);
    
    /* Postavljanje materijala za oblike */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambijent_materijala_oblika);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difuznost_materijala_oblika);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spekularnost_materijala_oblika);
    glMaterialf(GL_FRONT, GL_SHININESS, osvetljenje_oblika);
    
    /* Pravljenje/pomeranje izabranog oblika */
    if (oblik == 1){
        /* Pravljenje/pomeranje kocke */
        glPushMatrix();
        /*glColor3f(1,1,0);*/
        glTranslatef(pomeraj_po_x,pomeraj_po_y,pomeraj_po_z);
        glRotatef(rotacija_tela, 0, 0, 1);
        glutSolidCube(1);
        glPopMatrix();
    }
    else if (oblik == 9){
        /* Pravljenje/pomeranje tetraedra */
        glPushMatrix();
        /*glColor3f(1,0,1);*/
        glTranslatef(pomeraj_po_x,pomeraj_po_y,pomeraj_po_z);

        glRotatef(120, 1, 1, 0);
     /*   glRotatef(-45, 0, 1, 0);
       glRotatef(45, 0, 0, 1);*/
        glutWireTetrahedron();
        glPopMatrix();
    }
    else if (oblik == 2){
        /* Pravljenje/pomeranje sfere */
        glPushMatrix();
        /*glColor3f(1,0,1);*/
        glTranslatef(pomeraj_po_x,pomeraj_po_y,pomeraj_po_z);
        glRotatef(rotacija_tela, 0, 0, 1);
        glutSolidSphere(0.6,30,30);
        glPopMatrix();
    }
    else if (oblik == 3){
        /* Pravljenje/pomeranje valjka i postavljanje normale za valjak */
        float u;
        glPushMatrix();
       /* glColor3f(0,1,0);*/
        glTranslatef(pomeraj_po_x,pomeraj_po_y,pomeraj_po_z);
        glRotatef(rotacija_tela, 0, 0, 1);
        
        /* Pravljenje omotaca valjka */
        glBegin(GL_TRIANGLE_STRIP);
        for (u = 0; u < 2*(PI) + 0.1; u += 0.1) {
            glNormal3f(0.4*sin(u), 0, 0.4*cos(u));
            glVertex3f(0.4*sin(u), -0.7, 0.4*cos(u));
            glVertex3f(0.4*sin(u), 0.7, 0.4* cos(u));
        }
        
        glEnd();
        /* Pravljenje jedne baze valjka */
        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0,1,0);
        glVertex3f(0, 0.7, 0);
        for(u = 0; u < 2*(PI) + 0.1; u += 0.1){
            glNormal3f(0,1,0);
            glVertex3f(0.4*cos(u), 0.7, 0.4* sin(u));
        }
        glEnd();
        
        /* Pravljenje druge baze valjka */
        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0,-1,0);
        glVertex3f(0, -0.7, 0);
        for(u = 0; u < 2*(PI) + 0.1; u += 0.1){
            glNormal3f(0,-1,0);
            glVertex3f(0.4*cos(u), -0.7, 0.4* sin(u));
        }
        glEnd();
        glPopMatrix();
    }
    else if (oblik == 4){
        /* Pravljenje/pomeranje zvezde i postavljanje njenih normala */
        glPushMatrix();
        /*glColor3f(1,0,0);*/
        glTranslatef(pomeraj_po_x,pomeraj_po_y,pomeraj_po_z);
        glRotatef(rotacija_tela, 0, 0, 1);
        int i;
        float u;
        
        /* Pravljenje jedne baze zvezde */
        glBegin(GL_POLYGON);
            for(i = 0, u = 0; u < 2*(PI); i++, u+= 0.2*(PI)){
                if(i%2==0){
                    glNormal3f(0,0,-1);
                    glVertex3f(0.35*cos(u), 0.35*sin(u), -0.5);
                }
                else{
                    glNormal3f(0,0,-1);
                    glVertex3f(0.7*cos(u), 0.7*sin(u), -0.5);
                }
            }
        glEnd();
        
        /* Pravljenje omotaca zvezde */
        /* Omotac zvezde se sastoji od 10 pravougaonika koji su spojeni jednom stranicom i naizmenicno idu 
         u smeru spoljasnjost-unutrasnjost/unustrasnjost/spoljasnjost. Normale su nadjene preko vektorskog
         proizvoda dva vektora jednog pravougaonika (odnosno ravni u kojoj se on nalazi) */
        for(i = 0, u = 0; u < 2*(PI); i++, u+= 0.2*(PI)){
            if(i%2==0){
                glBegin(GL_POLYGON);
                glNormal3f(0.5*(0.7*sin(u+0.2*(PI))-0.35*sin(u)), -0.5*(0.7*cos(u+0.2*(PI))-0.35*cos(u)), 0);
                glVertex3f(0.35*cos(u), 0.35*sin(u), -0.5);
                glVertex3f(0.35*cos(u), 0.35*sin(u), 0);
                glVertex3f(0.7*cos(u+0.2*(PI)), 0.7*sin(u+0.2*(PI)), 0);
                glVertex3f(0.7*cos(u+0.2*(PI)), 0.7*sin(u+0.2*(PI)), -0.5);
                glEnd();
            }
            else{
                glBegin(GL_POLYGON);
                glNormal3f(0.5*(0.35*sin(u+0.2*(PI))-0.7*sin(u)), -0.5*(0.35*cos(u+0.2*(PI))-0.7*cos(u)), 0);
                glVertex3f(0.7*cos(u), 0.7*sin(u), -0.5);
                glVertex3f(0.7*cos(u), 0.7*sin(u), 0);
                glVertex3f(0.35*cos(u+0.2*(PI)), 0.35*sin(u+0.2*(PI)), 0);
                glVertex3f(0.35*cos(u+0.2*(PI)), 0.35*sin(u+0.2*(PI)), -0.5);
                glEnd();
            }
        }
        
        /* Pravljenje druge baze zvezde */
        glBegin(GL_POLYGON);
            for(i = 0, u = 0; u < 2*(PI); i++, u+= 0.2*(PI)){
                if(i%2==0){
                    glNormal3f(0,0,1);
                    glVertex3f(0.35*cos(u), 0.35*sin(u), 0);
                }
                else{
                    glNormal3f(0,0,1);
                    glVertex3f(0.7*cos(u), 0.7*sin(u), 0);
                }
            }
        glEnd();
        glPopMatrix();
    }
    
    /* Iskljucuje se svetlost */
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    
    /* Nova slika se salje na ekran */
    glutSwapBuffers();
    
}

static void on_keyboard(unsigned char key, int x, int y){
    
    switch(key){
    
        /* Ako korisnik pritisne Esc program se zavrsava */
        case 27:
            exit(0);
            break;
        
        /* Korisnik je izabrao kocku */
        case '1':
            oblik = 1;
            pomeraj_po_x = 0;
            pomeraj_po_y = 0;
            pomeraj_po_z = 2;
            rotacija_tela = 0;
            glutPostRedisplay();
            break;
            
        /* Korisnik je izabrao tetraedar */
        case '9':
            oblik = 9;
            pomeraj_po_x = 0;
            pomeraj_po_y = 0;
            pomeraj_po_z = 2;
            rotacija_tela = 0;
            glutPostRedisplay();
            break;
        
        /* Korisnik je izabrao sferu */
        case '2':
            oblik = 2;
            pomeraj_po_x = 0;
            pomeraj_po_y = 0;
            pomeraj_po_z = 2;
            rotacija_tela = 0;
            glutPostRedisplay();
            break;
            
        /* Korisnik je izabrao valjak */
        case '3':
            oblik = 3;
            pomeraj_po_x = 0;
            pomeraj_po_y = 0;
            pomeraj_po_z = 2;
            rotacija_tela = 0;
            glutPostRedisplay();
            break;
            
        /* Korisnik je izabrao zvezdu */
        case '4':
            oblik = 4;
            pomeraj_po_x = 0;
            pomeraj_po_y = 0;
            pomeraj_po_z = 2;
            rotacija_tela = 0;
            glutPostRedisplay();
            break;
            
        /* Pritiskom tastera e kamera se pomera ulevo */
        case 'e':
            ro = ro + 0.1;
            if (ro >= 2*(PI)){
                ro = ro - 2*(PI);
            }
            glutPostRedisplay();
            break;
            
        /* Pritiskom tastera q kamera se pomera udesno */
        case 'q':
            ro = ro - 0.1;
            if (ro < 0){
                ro = ro + 2*(PI);
            }
            glutPostRedisplay();
            break;
        
        /* Kamera se pomera ka dole */
        case 's':
            if (phi < (PI)/2 - 0.1){
                phi = phi + 0.1;
            }
            glutPostRedisplay();
            break;
        
        /* Kamera se pomera ka gore */
        case 'w':
            if (phi > 0.2){
                phi = phi - 0.1;
            }
            glutPostRedisplay();
            break;
            
        /* Telo se rotira ulevo */
        case 'u':
            if (pomeraj_po_z > 0.4){
                rotacija_tela += 18;
                if(fabs(rotacija_tela - 360) <= 0.000001){
                    rotacija_tela -= 360;
                }
            }
            glutPostRedisplay();
            break;
        
        /* Telo se rotira udesno */
        case 'o':
            if (pomeraj_po_z > 0.4){
                rotacija_tela -= 18;
                if(fabs(rotacija_tela) <= 0.000001){
                    rotacija_tela += 360;
                }
            }
            glutPostRedisplay();
            break;
            
        /* Telo se translira po x osi unapred */
        case 'i':
            if (pomeraj_po_x < 5 && oblik != 0 && pomeraj_po_z > 0.4 ){
                pomeraj_po_x += 0.1;
                glutPostRedisplay();
            }
            break;
           
        /* Telo se translira po x osi unazad */
        case 'k':
            if (pomeraj_po_x > -5 && oblik != 0 && pomeraj_po_z > 0.4 ){
                pomeraj_po_x -= 0.1;
                glutPostRedisplay();
            }
            break;
        
        /* Telo se translira po y osi unapred */
        case 'j':
            if (pomeraj_po_y < 5 && oblik != 0 && pomeraj_po_z > 0.4 ){
                pomeraj_po_y += 0.1;
                glutPostRedisplay();
        }
            break;
        
        /* Telo se translira po y osi unapred */
        case 'l':
            if (pomeraj_po_y > -5 && oblik != 0 && pomeraj_po_z > 0.4 ){
                pomeraj_po_y -= 0.1;
                glutPostRedisplay();
            }
            break;
          
        /* Telo se translira po z osi ka gore */
        case 'y':
            if (pomeraj_po_z < 5 && oblik != 0){
                pomeraj_po_z += 0.1;
                glutPostRedisplay();
            }
            break;
          
        /* Telo se translira po z osi ka dole
           Ako je telo iznad svog kalupa, moze da udje u kalup
           Ako se telo vise ne vidi, onda se brise */
        case 'h':
            
            switch(oblik){
                /* Ako je trenutni oblik kocka */
                case 1:
                    if ((pomeraj_po_z > 0.5 
                        || (pomeraj_po_z > -0.5  && (int)rotacija_tela % 90 == 0
                        && fabs(centar_rupe[0] - pomeraj_po_x) <= 0.000001 && fabs(centar_rupe[1] - pomeraj_po_y) <= 0.000001))
                        && oblik != 0){
                        pomeraj_po_z -= 0.1;
                        if (fabs(pomeraj_po_z + 0.5) <= 0.000001){
                            novi_objekat();
                            pomeraj_po_x = 0;
                            pomeraj_po_y = 0;
                            pomeraj_po_z = 2;
                        }
                        glutPostRedisplay();
                    }
                    break;
                    
                /* Ako je trenutni oblik lopta */
                case 2:
                     if ((pomeraj_po_z > 0.5 
                        || (pomeraj_po_z > -0.5 
                        && fabs(centar_rupe2[0] - pomeraj_po_x) <= 0.000001 && fabs(centar_rupe2[1] - pomeraj_po_y) <= 0.000001))
                        && oblik != 0){
                        pomeraj_po_z -= 0.1;
                        if (fabs(pomeraj_po_z + 0.5) <= 0.000001){
                            novi_objekat();
                            pomeraj_po_x = 0;
                            pomeraj_po_y = 0;
                            pomeraj_po_z = 2;
                        }
                        glutPostRedisplay();
                    }
                    break;
                  
                /* Ako je trenutni oblik valjak */
                case 3:
                     if ((pomeraj_po_z > 0.5 
                        || (pomeraj_po_z > -0.5 && (int)rotacija_tela % 180 == 0
                        && fabs(centar_rupe3[0] - pomeraj_po_x) <= 0.000001 && fabs(centar_rupe3[1] - pomeraj_po_y) <= 0.000001))
                        && oblik != 0){
                        pomeraj_po_z -= 0.1;
                        if (fabs(pomeraj_po_z + 0.5) <= 0.000001){
                            novi_objekat();
                            pomeraj_po_x = 0;
                            pomeraj_po_y = 0;
                            pomeraj_po_z = 2;
                        }
                        glutPostRedisplay();
                    }
                    break;
                    
                /* Ako je ternutni oblik zvezda */
                case 4:
                     if ((pomeraj_po_z > 0.5 
                        || (pomeraj_po_z > -0.5 && (int)rotacija_tela % 72 == 0
                        && fabs(centar_rupe4[0] - pomeraj_po_x) <= 0.000001 && fabs(centar_rupe4[1] - pomeraj_po_y) <= 0.000001))
                        && oblik != 0){
                        pomeraj_po_z -= 0.1;
                        /*printf("%f %f %f %f %f\n", pomeraj_po_x, pomeraj_po_y, pomeraj_po_z, centar_rupe4[0], centar_rupe4[1]);*/
                        if (fabs(pomeraj_po_z) <= 0.000001){
                            novi_objekat();
                            pomeraj_po_x = 0;
                            pomeraj_po_y = 0;
                            pomeraj_po_z = 2;
                        }
                        glutPostRedisplay();
                    }
                    break;
            }
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
    glutTimerFunc(100, on_timer, 0);
    
    /* Obavljanje OpenGL inicijalizacije */
    initialize();
    
    /* Postavljanje pocetnog ugla */
    ro = (PI)/4;
    phi = (PI)/4;
    
    /* Postavljanje pocetnog ugla i smera kretanja pozicije svetlosti */
    beta = 0;
    smer_pozicije_svetlosti = 1;
    
    /* Postavljanje pocetnih pomeraja */
    pomeraj_po_x = 0;
    pomeraj_po_y = 0;
    pomeraj_po_z = 2;
    
    /* Postavljanje koordinata centara kalupa */
    centar_rupe[0] = 2.5;
    centar_rupe[1] = 2.5;
    centar_rupe2[0] = -2;
    centar_rupe2[1] = 2;
    centar_rupe3[0] = -1.4;
    centar_rupe3[1] = -1.7;
    centar_rupe4[0] = 3;
    centar_rupe4[1] = -2;

    /* Ulazak u glavnu petlju */
    glutMainLoop();
    
    return 0;
    
}
