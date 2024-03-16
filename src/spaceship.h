typedef struct spaceship
{
    float sx; //Screen x
    float sy; //Screen y
    float heading; //Direction
    float speed; 
    int gone; //Alive?
    ALLEGRO_COLOR color;
} spaceship;