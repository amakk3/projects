#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change constant kYourNetID to store your netID 
 *    - your submission will be manually inspected to ensure
 *      you have used the exact string that is your netID
 *    - thus, it is vital you understand what your netID is
 *    - ex: Professor Reckinger's email is scotreck@uic.edu, so
 *          Professor Reckinger's netID is scotreck     
 *    - ex: Professor Kidane's email is ekidan2@uic.edu, so
 *          Professor Kidane's netID is ekidan2     
 *    - ex: Student Sparky's email is sspark211@uic.edu, so
 *          Student Sparky's netID is sspark211 
 * WARNING: Once you've set set this constant and started 
 * exploring your maze, do NOT edit the value of kYourNetID. 
 * Changing kYourNetID will change which maze you get back, 
 * which might invalidate all your hard work!
 */
const string kYourNetID = "amakk3";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "SENSSEENNW";
const string kPathOutOfTwistyMaze = "WNNSSNNWESSNN";

bool isPathToFreedom(MazeCell *start, const string& moves) {
    set<MazeCell*> items;
    for (size_t i = 0; i <= moves.size(); ++i) { // loop through moves
        if (start->whatsHere == "Spellbook" || start->whatsHere == "Potion" || start->whatsHere == "Wand") { // check if item is in cell
            items.insert(start);
        }
        if (i < moves.size()) { //if current move is not the last move, move to next cell
            if (moves[i] == 'N') {
                if (start->north == nullptr)  {
                    return false;
                } else {
                    start = start->north;
                }
            } else if (moves[i] == 'S') {
                if (start->south == nullptr)  {
                    return false;
                } else {
                    start = start->south;
                }
            } else if (moves[i] == 'E') {
                if (start->east == nullptr)  {
                    return false;
                } else {
                    start = start->east;
                }
            } else if (moves[i] == 'W') {
                if (start->west == nullptr)  {
                    return false;
                } else {
                    start = start->west;
                }
            } else {
                return false;
            }
        }
    }
    if (items.size() == 3) { //return true if all items are found
        return true;
    } else {
        return false;
    }
}
