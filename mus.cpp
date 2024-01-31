#include <iostream>
using namespace std;


int main()
{
    cout << "Welcome to music player" << endl;
    int play;
    do{
      cout << "Welcome to music player" << endl;
      cout << "Songs: " << endl;
      cout << "1) 295 " << endl;
      cout << "2) viah" << endl;
      cout << "3) Bikhra" << endl;
      cout << "4) agency" << endl;
      cout << "5) Afsanay" << endl;
      cout << "0) Exit" << endl;
      cin >> play;
    if(play == 1)
    {
        cout << "use CTRL+c to finish music" << endl;
        system("canberra-gtk-play -f 295.ogg");
        
    }
    else if(play == 2)
    {
        cout << "use CTRL+c to finish music" << endl;
        system("canberra-gtk-play -f viah.ogg");
        
    
    }
    else if(play == 3)
    {
        cout << "use CTRL+c to finish music" << endl;
        system("canberra-gtk-play -f bikhra.ogg");
    
    }

    else if(play == 4)
    {
        cout << "use CTRL+c to finish music" << endl;
        system("canberra-gtk-play -f agency.ogg");
    
    }
    else if(play == 5)
    {
        cout << "use CTRL+c to finish music" << endl;
        system("canberra-gtk-play -f afsanay.ogg");
    
    }    
    
    }while(play != 0);
 
    return 0;
}