double timer_erfasse_zeitpunkt(void);
double timer_berechne_vergangene_zeit(double t1, double t2)
{
 double diff= t2 - t1;
 return (diff/ 90e6);   
}