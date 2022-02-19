// Hokeemon.cpp
// Alexander Le
// 04/09/2019

// Preprocessor Directives
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <memory> 
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <new>
#include <thread>

// Namespace declarations
using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

// Function Prototypes 
void HokeeSay(const string& , unsigned int); 
void HokeeSay(const string& , const string& , unsigned int);
void Pikachu(); // Displays a Pikachu drawn in Ascii characters
void PlayerGreeting(); // Greet the player
void ShowHowToPlay(); // Displays how the game works to the player
char PlayerActions(); // Display possible actions with Hokeemon

// Specification C2 - Virtual Class Creature
class Creature
{
  private: 
  // The Hokee's name and action
    string Hokee, HokeeAction; 
    int hunger, boredom;
  public:
    int hun, bore, turns;
  // Constructor with 3 arguments, initialization list
    Creature(string name, int x, int y) : Hokee(name), hunger(y),  boredom(x) 
    { // Program Greeting
      cout << "——————————————----------------------------------------————————\n";
      cout << "                          Hokeemon                            \n";
      cout << "——————————————----------------------------------------————————\n";
      HokeeSay("Hello! Welcome ", name, 93);
      HokeeSay("!\n\nAre you ready to hook'em all? [ yes / no ]", 93);
      cout << "\n\n-> "; 
      // Base Specfication 1
      // Use a constructor to initialize hunger and boredom to random numbers between 0 - 5.
      /* initialize random starting seed: */
      srand (time(NULL)); 
      x = (rand() %5); 
      y = (rand() %5);
      hun = (rand() %5); 
      bore = (rand() %5);  } 
  // Specification A2 - Copy Constructor/Assignment Operator
  Creature(const Creature *Trainer2);
  // Method to decide state of Hookee
  // Hungry(feedme) / Bored(play) Hookee
    virtual void HokeeState(string n) { cout << n << " wants to play!\n";}
  // Hookee state % random % +4
  // Specification C1 - PassTime() method
    void PassTime() { hunger++; hun = hunger; boredom++; bore = boredom; }
    // Boredom moods: >15: Mad, 10-14: Frustrated, 5-9: OK, 0-4, Happy
    //Count how many turns your Hokeemon was happy.
    //Specification B2 - Moods
    int HokeeMood(int, int); // will preform based on HookeeState
    void TurnCounter(int& count); // Logs turns into turns.txt
  // Destructor with bye message
  virtual ~Creature() {cout << "\nThanks for playing! CYA Byeeeee~\n";}
};

// Specification C3 - Child Class
class HappyHokee : public Creature 
{
public:
  void HokeeState(string n) {cout << n << " is happy and wants to play!\n";}
};
// Specification B3 - Second Child Class
class BoredHokee : public Creature 
{
public:
  void HokeeState(string n) {cout << n << " is bored and wants to play!\n";}
};

class HungryHokee : public Creature 
{
public:
  void HokeeState(string n) {cout << n << " is hungry and wants food!\n";}
};

class SadHokee : public Creature 
{
public:
  void HokeeState(string n) {cout << n << " is sad!!!\n";}
};

struct HokeeType
{ // All is puclic
    string fire = "fire", zappyZap = "electric", ice = "ice", h2o =  "water", rock = "rock",  floatyFloat = "air";
    // Determine the type of the Hokeemon
    void magic();
};

int main() 
{
  const int S = 50;
  int bored = 0, hungry = 0, currentMood = 0;
  // charcater variable to hold player interactions with a Hokeemon
  char action;
  // C-string to hold the player's answer 
  char playerAnswer[S] = "Cactus";
  // create a C-string to hold the player name
  char name[S];
  // Create a C-string to hold Hokeenames
  char hokeeName[S];
  // Player Greeting
  PlayerGreeting();
  // Prompt player for name.
  HokeeSay("Please type in your name: ", 93);
  cin.getline(name, S);
  // Create a Creature shared pointer called Trainer to manage the Hookeemon
  shared_ptr<Creature> Trainer = make_shared<Creature>(name, bored, hungry);
  //Creature Trainer(name, bored, hungry);
  cin >> playerAnswer; 
  // Process the player's answer
  if (playerAnswer[0] == 'Y' || playerAnswer[0] == 'y')
  {
    HokeeSay("\nOkay! Let's play!\n",93); // yay!
    cout << endl << name;
    HokeeSay(", I believe you can be the greatest hokeemon\ntrainer EVER. I believe in you!!! Good luck!\n", 93);
    cout << "\n\n\n\n\n\n" << flush; 
    Pikachu();
    HokeeSay("Hi, I'm Pikachu and unfortuantely copyrighted by\nNintendo Entertainment. Let's just pretend I'm Hokeechu OKAY? :D\n", 93);
  }
  else
  {
    // Specification A3 - Code Protection
    assert(playerAnswer[0] == 'Y' || playerAnswer[0] == 'y');
    cout << "\n(Even though you didn't)"; 
    return 0; // Aw bye
  }

  // Create a HokeeType object to assign the player's first Hokee a type. 
  HokeeType assign;

  ShowHowToPlay();

  // Specification A1 - Critter Name
  cout << "Please name your very first Hokeemon! It's a "; 
  assign.magic();
  cout << " type!\nMake the name cool and impressive but limited to 50 characters.\n-> ";

  // Get full name of Hokee
  fgets (hokeeName, 50, stdin);
  scanf ("%[^\n]%*c", hokeeName);
  cout << hokeeName << " is happy to meet you!!\n";

  // Display menu-based actions
  action = PlayerActions();
  do {
    switch(action){
      case 'A': 
        // Assign hungry to value initialized from the base Creature class constructor
        hungry = Trainer->hun;
        // Decrement the hunger state of the Hokeemon
        hungry--;
        HokeeSay("You feed me! my hunger is now at ", 93);
        cout << hungry << '!' << endl; 
        cout << endl;
        // Get the current mood based on satisfaction levels
        currentMood = Trainer->HokeeMood(hungry, bored); 
        if (hungry == 0)
          cout << "\nYou've filled me up! Burrrp!! I'm good on food now!\n";
        if (hungry == 4)
          cout << "\nThank you! I was starving! Let's play!\n";
          // Pass the time
          Trainer->PassTime();
          // Prompt again
          action = PlayerActions();
        break;
      case 'B':
        // Assign boredom to value initialized from the base Creature class constructor
        bored = Trainer->bore;
        // Decrement the boredom state of the Hokeemon
        bored--;
        HokeeSay("You played with me! my boredom is now at ", 93);
        cout << bored << '!' << endl; 

        // Get the current mood based on satisfaction levels
        currentMood = Trainer->HokeeMood(hungry, bored); 

        if (bored == 0)
          cout << "\nYou've played with me! I'm tired now so I'll take a short nap!\n";
        if (bored == 4)
          cout << "\nThank you! I was SUPER bored!!\n";
          // Pass the time
          Trainer->PassTime();
          // Prompt again
          action = PlayerActions();
        break; 
      case 'C':
        // Assign hungry to value initialized from the base Creature class constructor
        hungry = Trainer->hun;
        // Assign boredom to value initialized from the base Creature class constructor
        bored = Trainer->bore;
        // Display states
        cout << "\nThe current states of this Hokeemon are: \n - Boredom: ";
        cout << bored << " \n - Hunger: " << hungry << " " << endl; 

        // Get the current mood based on satisfaction levels
        currentMood = Trainer->HokeeMood(hungry, bored); 

        if (hungry == 0)
          cout << "\n\n It's currently full! Maybe you should play with it!\n";
        if (hungry == 4)
          cout << "\nLooks like it's really hungry! You should feed it!!\n";
        if (bored == 0)
          cout << "\nIt was playing by itself, its tired now, maybe you should feed it!\n";
        if (bored == 4)
          cout << "\nIts really bored and starting to get sad! Play with it!\n";
          // Pass the time
          Trainer->PassTime();
          // Prompt again
          action = PlayerActions();
        break;
      case 'D':
        cout << "\nIt took " << Trainer->turns;
        cout << " turns for Hokee to be happy.\n";
        Trainer = nullptr; 
        break;
      case 'E':
        return 0;
      default: 
        // Specification B1 - Validate Input
        if (action != 'A' && action != 'B' && action != 'C' && action != 'D' && action != 'E')
        {
          cout << "Sorry! that is invalid! Please try again!!\n";
          // Re-prompt and update action
          action = PlayerActions();
        }
      }
  } while(action !='E');

  // Get Hokee state
  Trainer->HokeeState(hokeeName);
  return 0;
}

// A stream is a hardware independent abstraction 
// https://ps.uci.edu/~cyu/p231C/LectureNotes/
// http://www.karlsims.com/papers/siggraph94.pdf
/* https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-034-artificial-intelligence-fall-2010/readings/MIT6_034F10_bayes.pdf

*/

// front-end functions for user interfacing effects
void HokeeSay(const string& message, unsigned int millis_per_char)
{
    // for each charater in the string
    for (const char c: message)
    {
        // flush the existing buffer and display string.
        cout << c << flush;
        
        // latency for the string as if it was typed out.
        sleep_for(milliseconds(millis_per_char));
    }
}
// overloaded HokeeSay to take an additional const string
void HokeeSay(const string& greeting, const string& message, unsigned int millis_per_char)
{
    // for each charater in the string
    for (const char c: greeting)
    {
        // flush the existing buffer and display string.
        cout << c << flush;
        
        // latency for the string as if it was typed out.
        sleep_for(milliseconds(millis_per_char));
    }
    // for each charater in the string
    for (const char c: message)
    {
        // flush the existing buffer and display string.
        cout << c << flush;
        
        // latency for the string as if it was typed out.
        sleep_for(milliseconds(millis_per_char));
    }
}

void HokeeType::magic()
{
   /* initialize random starting seed: */
  srand (time(NULL));
  int random = (rand() %7);
  switch (random)
  {
    case 1: 
      cout << fire; // fire type Hokeemon
      break;
    case 2: 
      cout << zappyZap; // electric type Hokeemon
      break;
    case 3:
      cout << ice; // ice type Hokeemon
      break;
    case 4:
      cout << h2o; // water type Hokeemon
      break;
    case 5:
      cout << rock; // rock type Hokeemon
      break;
    case 6:
      cout << floatyFloat; // // air type Hokeemon
      break;
  }
}

// print a friendly ice cream hungry pikachu
void Pikachu()
{
  cout <<	"\n\nhi!..__	" << endl;
  cout << "$$$$  `---.__	" << endl;
  cout << "  $$        `--.                          ___.---$$$$$$\". " << endl;	
  cout << "   `$$$           `.__.------.__     __.---'      $$$$\"              .	" << endl;
  cout << "     \"$$          -'            `-.-'            $$$\"              .'|	" << endl;
  cout << "       \".                                       $$\"             _.'  |	" << endl;
  cout << "         `.   /                              ...\"             .'     |	" << endl;
  cout << "           `./                           ..::-'            _.'       |	" << endl;
  cout << "            /                         .:::-'            .-'         .'	" << endl;
  cout << "           :                          ::''\\          _.'            |	" << endl;
  cout << "          .' .-.             .-.           `.      .'               |	" << endl;
  cout << "          : /'$$|           .@\"$\\           `.   .'              _.-'	" << endl;
  cout << "         .'|ICE$|          |CREAM|           |  <            _.-'	" << endl;
  cout << "         | `:$$:'          :$$$$$:           `.  `.       .-'	" << endl;
  cout << "         :                  `\"--'             |    `-.     \\	" << endl;
  cout << "        :##.       ==             .###.       `.      `.    `\\	" << endl;
  cout << "        |##:                      :###:        |        >     >	" << endl;
  cout << "        |#'     `..'`..'          `###'        x:      /     /		" << endl;
  cout << "         \\                                   xXX|     /    ./	" << endl;
  cout << "          \\                                xXXX'|    /   ./	" << endl;
  cout << "          /`-.                                  `.  /   /	" << endl;
  cout << "         :    `-  ...........,                   | /  .'	" << endl;
  cout << "         |         ``:::::::'       .            |<    `.	" << endl;
  cout << "         |             ```          |           x| \\ `.:``.	" << endl;
  cout << "         |                         .'    /'   xXX|  `:`M`M':.	" << endl;
  cout << "         |    |                    ;    /:' xXXX'|  -'MMMMM:'	" << endl;
  cout << "         `.  .'                   :    /:'       |-'MMMM.-'	" << endl;
  cout << "          |  |                   .'   /'        .'ICE.-'	" << endl;
  cout << "          `'`'                   :  ,'          |MMM<	" << endl;
  cout << "            |                     `'            |cream\\	" << endl;
  cout << "             \\                                  :MM.-'	" << endl;
  cout << "              \\                 |              .''	" << endl;
  cout << "               \\.               `.            /	" << endl;
  cout << "                /     .:::::::.. :           /	" << endl;
  cout << "               |     .:::::::::::`.         /	" << endl;
  cout << "               |   .:::------------\\       /	" << endl;
  cout << "              /   .''               >::'  /	" << endl;
  cout << "              `',:                 :    .'	" << endl;
}

// Say hello to the player with a giant charizard
void PlayerGreeting()
{
  cout << "                 .\"-,.__'\n";
  cout << "                 `.     `.  ,\n";
  cout << "              .--'  .._,'\"-' `.\n";
  cout << "             .    .'         `\'" << endl;
  cout << "             `.   / HOKEEMON ,\'" << endl;
  cout << "               `  '--.   ,-\"'\" " << endl;
  cout << "               `'`   |  \"" << endl; 
  cout << "                   -. \\  |" << endl; 
  cout << "                    `--\\.'      ___." << endl; 
  cout << "                         \\      ._, \\." << endl;
  cout << "               _.,        `.   <  <\\ Hi lol.         ." << endl;
  cout << "             ,' '           `, `.   | \\            ( `" << endl;
  cout << "          ../, `.            `  |    .\\`.           \\ \\_" << endl;
  cout << "         ,' ,..  .           _.,'    ||\\|            )  '\"." << endl;
  cout << "        , ,'   \\           ,'.-.`-._,'  |           .  _._`." << endl;
  cout << "      ,' /      \\ \\        `' ' `--/   | \\          / /   ..\\ " << endl; 
  cout << "    .'  /        \\ .         |\\__ - _ ,'` `        / /     `.`." << endl;
  cout << "    |  '          ..         `-...-\"  |  `-'      / /        . `. " << endl;  
  cout << "    | /            \\\\            |    |          / /          `. `." << endl;
  cout << "   , /            .   .          |    |         / /             ` `" << endl;
  cout << "  / /          ,. ,`._ `-_       |    |  _   ,-' /                ` \\ " << endl;
  cout << " / .           \"`_/. `-_ \\_,.  ,'    +-' `-'  _,        ..,-.      \\`." << endl;
  cout << "  '         .--    ,'   `    '.       \\\\__.---'     _   .'   '      \\ \\ " << endl;
  cout << "' /          `.'    \\     .' /          \\..      ,_|/   `.  ,'`      \\ ' " << endl;
  cout << "|'      _.-\"\"` `.    \\ _,'  `            \\ `.___`.'\"`-.  , |   |    | \\ " << endl;
  cout << "||    ,'      `. `.   '       _,...._        `  |    `/ '  |   '     .|" << endl;
  cout << "||  ,'          `. ;.,.---' ,'       `.   `.. `-\\'  .-\\' /_ .'    ;_   ||" << endl;
  cout << "|| '                     / /           `   | `   ,'   ,' '.    !  `. ||" << endl;
  cout << "||/            _,-------/ '              . |  `-'    /         /    `||" << endl;
  cout << " |          ,' .-   ,' ||               | .-.        `.      .'     ||" << endl;
  cout << " `'        ,'    `\".'    |               |    `.        '. -.'       `'" << endl;
  cout << "          /      ,'      |               |,'    \\-.._,.'/'" << endl; 
  cout << "          .     /        .               .       \\    .''" << endl;
  /*
  cout << "        .`.    |         `.             //         :_,'.'" << endl; 
  cout << "          \\ `...\\   _     ,'-.        .'         //_.-'" << endl;
  cout << "           `-.__ `,  `'   .  _.>----\".  _  __  //" << endl;
  */
}

char PlayerActions(){
  char answer = 't'; 
  cout << "\nEnter one of these letters to interact with your Hokeemon!";
  cout << "\n---------------------------\n"; 
  cout << "|   [A] to feed.          |\n";
  cout << "|   [B] to play.          |\n";
  cout << "|   [C] to listen.        |\n";
  cout << "|   [D] to view turns.    |\n";
  cout << "|   [E] to exit.          |\n";
  cout << "---------------------------" << endl; // flush string buffer 
  cin >> answer;
  return answer; 
}

void ShowHowToPlay()
{
  // Program Description
  cout << "\nWelcome to a game where you take care of and train\nmagical creatures called Hokeemon with magical abilities!\n\n";

  cout << "Your goal is to play and feed your Hokeemon untill\nit's adequately well-fed and happy, you accomplish\nthis by playing and deeding it.\n\n";
  
  cout << "Overtime, your Hokeemon will get bored and hungry again so be careful!\nHokeemon Satisfaction levels range from 0 - 5, \nwith reaching 0 being a state of high satisfaction!\n\n";
}

//Specification B2 - Moods
int Creature::HokeeMood(int hungryState, int boredState)
{
  // Variable to hold the current mood
  // Variable to the count turns till Happy is reached
  int mood;
  // Boredom moods: >15: Mad, 10-14: Frustrated, 5-9: OK, 0-4, Happy
  // Count how many turns your Hokeemon was happy.
    if (hungryState == 5 && boredState == 5) // Mad
    {
      mood = 15;
      turns++;
      TurnCounter(turns);
      cout << "\nWarning!!\b Your Hokeemon is currently very mad!\n";
    }
    if (hungryState == 5 && boredState == 5) // Frustrated
    {
      mood = 10; 
      turns++;
      TurnCounter(turns);
      cout << "\nWarning!!\b Your Hokeemon is currently frustrated!\n";
    }
    if (hungryState <= 3 && boredState <= 3) // OK
    {
      mood = 5;
      turns++;
      TurnCounter(turns);
      cout << "\nYour Hokeemon is currently OK but keep on playing and feeding it!\n";
    }
    if (hungryState <= 2 && boredState <= 2) // Happy
    {
      mood = 0;
      cout << "\nNice Job! It took " << turns << " turns for your\nHokeemon to reach happiness!\n"; 
    }
  return mood;
}

void Creature::TurnCounter(int& count){
   fstream file; // declare an object of fstream class
   file.open("turns.txt", ios :: out | ios :: app); // open file in append mode
   if (file.fail()) { // check if file is opened successfully
      // file opening failed
      cout << "\nError Opening file ... " << endl;
   }
   else {
      file << count << endl; // Append the line to the file
   }
}
