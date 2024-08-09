/*-------------------------------------------
Program 1: Scrambler
Course: CS 141, Spring 2023, UIC
System: Replit
Author: Abrar Makki
------------------------------------------- */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Scrambler {
private:
  string og_game = "";
  string game = "";
  string board_to_show;
  int rows;
  int size;
  vector<string> v;
  vector<string> moves;
public:
  string move_func(string curr_board, char dir, int idx, int rows);
  string scrambler_init(vector<string> &dict_words, vector<string> &grid,int num, vector<string> &v);
  vector<string> make_grid(int num);
  string jumble_board(string curr_board, int size, int rows);
  Scrambler(const string &path, const int size);
  string str() const;
  void try_move(const string &cmd);
  bool is_over() const;
  string display_solution();
  vector<string> get_words() const;
  void fix_board(string board);
};
string Scrambler::move_func(string curr_board, char dir, int idx, int rows) {
  vector<int> positions(0);
  string board = curr_board;
  string temp = "";
  int start = (curr_board.size() / rows) * 2;
  int p = 0;
  int lr_start = start * (idx + 1);
  switch (dir) {
  case 'u':
    for (int i = start; i < curr_board.size() - start / 2; ++i) {
      if (i % 4 == 0 && i != start) {
        if (idx == p) {
          temp += board[i];
          positions.push_back(i);
          p = idx;
          i += start - 1;
          continue;
        }
        p += 1;
      }
    }
    for (int j = 0; j < positions.size(); ++j) {
      board[positions[j]] = temp[j + 1];
    }
    board[positions.back()] = temp[0];
    break;
  case 'd':
    for (int i = start; i < curr_board.size() - start / 2; ++i) {
      if (i % 4 == 0 && i != start) {
        if (idx == p) {
          temp += board[i];
          positions.push_back(i);
          p = idx;
          i += start - 1;
          continue;
        }
        p += 1;
      }
    }
    for (int j = 0; j < positions.size() - 1; ++j) {
      board[positions[j + 1]] = temp[j];
    }
    board[positions.front()] = temp.back();
    break;
  case 'l':
    for (int i = lr_start; i < (lr_start + start / 2); ++i) {
      if (i % 4 == 0 && i != lr_start) {
        temp += board[i];
        positions.push_back(i);
      }
    }
    for (int j = 0; j < positions.size(); ++j) {
      board[positions[j]] = temp[j + 1];
    }
    board[positions.back()] = temp[0];
    break;
  case 'r':
    for (int i = lr_start; i < (lr_start + start / 2); ++i) {
      if (i % 4 == 0 && i != lr_start) {
        temp += board[i];
        positions.push_back(i);
      }
    }
    for (int j = 0; j < positions.size() - 1; ++j) {
      board[positions[j + 1]] = temp[j];
    }
    board[positions.front()] = temp.back();
    break;
  }
  return board;
}
string Scrambler::jumble_board(string curr_board, int size, int rows) {
  string move;
  int rand_int = rand() % 8;
  int nmoves = rand_int + 3;
  string next_board = curr_board;
  for (int i = 1; i < nmoves; ++i) {
    int rand_idx = rand() % size;
    if (i % 2 == 0) {
      int u_or_d = rand() % 2;
      switch (u_or_d) {
      case 0:
        move = "c" + to_string(rand_idx + 1) + "u";
        moves.push_back(move);
        next_board = move_func(next_board, 'u', rand_idx, rows);
        break;
      case 1:
        move = "c" + to_string(rand_idx + 1) + "d";
        moves.push_back(move);
        next_board = move_func(next_board, 'd', rand_idx, rows);
        break;
      }
    } else {
      int l_or_r = rand() % 2;
      switch (l_or_r) {
      case 0:
        move = "r" + to_string(rand_idx + 1) + "l";
        moves.push_back(move);
        next_board = move_func(next_board, 'l', rand_idx, rows);
        break;
      case 1:
        move = "r" + to_string(rand_idx + 1) + "r";
        moves.push_back(move);
        next_board = move_func(next_board, 'r', rand_idx, rows);
        break;
      }
    }
  }
  return next_board;
}
vector<string> Scrambler::make_grid(int num) {
  vector<string> grid;
  grid.push_back(" ");
  grid.push_back("   ");
  for (int k = 0; k < num; ++k) {
    grid[0] += "   " + to_string(k + 1);
    grid[1] += "----";
  }
  for (int i = 0; i < num; ++i) {
    grid.push_back(to_string(i + 1));
    grid.push_back(grid[1]);
  }
  for (int j = 0; j < grid.size(); ++j) {
    if (j % 2 == 0 && j != 0) {
      for (int k = 0; k < num; ++k) {
        grid[j] += " |  ";
      }
      grid[j] += " |";
    }
  }
  grid[0] += "  ";
  for (int j = 0; j < grid.size(); ++j) {
    grid[j] += "\n";
  }
  return grid;
}
string Scrambler::scrambler_init(vector<string> &dict_words,
                                 vector<string> &grid, int num,
                                 vector<string> &v) {
  int remain_spaces = num;
  int o = 0;
  bool insert = false;
  string curr_word;
  for (int j = 2; j < grid.size(); j += 2) {
    remain_spaces = num;
    insert = false;
    for (int i = 0; i < grid[j].size(); ++i) {
      while (remain_spaces > 2 && insert == false) {
        curr_word = dict_words[rand() % dict_words.size()];
        if (remain_spaces >= curr_word.size()) {
          o = 0;
          for (int l = 0; l < grid[j].size(); ++l) {
            if (l % 4 == 0 && l != 0) {
              grid[j][l] = curr_word.at(o);
              o += 1;
            } else if (o >= curr_word.size()) {
              insert = true;
              v.push_back(curr_word);
              break;
            }
          }
          remain_spaces = remain_spaces - curr_word.size();
          if (remain_spaces > 3) {
            insert = false;
            int u = curr_word.size() * 4;
            while (remain_spaces > 2 && insert == false) {
              curr_word = dict_words[rand() % dict_words.size()];
              if (remain_spaces > curr_word.size()) {
                o = 0;
                for (int l = u; l < grid[j].size(); ++l) {
                  if (l % 4 == 0 && l != u && l != u + 4) {
                    grid[j][l] = curr_word.at(o);
                    o += 1;
                  } else if (o >= curr_word.size()) {
                    insert = true;
                    v.push_back(curr_word);
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  string curr_board = "";
  for (int i = 0; i < grid.size(); ++i) {
    curr_board += grid[i];
  }
  curr_board = jumble_board(curr_board, num, grid.size());
  return curr_board;
}
/////////////////////////////////////////////////////////////////////////

void Scrambler::fix_board(string board) {
  int row = game.size() / rows;
  board_to_show = game;
  for (int i = 0; i < row; ++i) {
    if (i > row - 4) {
      board_to_show.erase(i, 2);
      break;
    }
  }
  board_to_show.pop_back();
}
Scrambler::Scrambler(const string &path, const int size) {
  fstream file;
  vector<string> dict_words;
  file.open(path);
  string dict_word;
  if (!file.is_open()) {
    cout << "failure: dictionary not found";
  } else {
    while (getline(file, dict_word)) {
      dict_words.push_back(dict_word);
    }
  }
  vector<string> grid;
  grid = make_grid(size);
  game = scrambler_init(dict_words, grid, size, v);

  this->rows = grid.size();
  this->og_game = game;
  this->size = size;
  fix_board(game);
}
string Scrambler::str() const { return board_to_show; }
void Scrambler::try_move(const string &cmd) {
    if (cmd.size() < 2) {
        this->game = og_game;
        fix_board(game);
    } else {
  char rc, dir, restart;
  rc = dir = restart = ' ';
  string c = "";
  string moved_board;
  int number = 0;
  rc = tolower(cmd[0]);
  c = cmd[1];
  number = stoi(c);
  dir = tolower(cmd[2]);
  switch (rc) {
  case 'c':
    if (dir == 'd') {
      moved_board = move_func(game, 'd', number - 1, rows);
    } else {
      moved_board = move_func(game, 'u', number - 1, rows);
    }
    break;
  case 'r':
    if (dir == 'r') {
      moved_board = move_func(game, 'r', number - 1, rows);
    } else {
      moved_board = move_func(game, 'l', number - 1, rows);
    }
    break;
  }
  game = moved_board;
  fix_board(game);
    }
}
bool has_only_spaces(const std::string &str) {
  return str.find_first_not_of(' ') == str.npos || str.empty();
}
bool Scrambler::is_over() const {
  int start = (game.size() / rows) * 2;
  int counter = 0;
  vector<string> words(v.size(), "");
  int o = 0;
  for (int j = start; j < game.size(); j += start) {
    for (int i = j; i < j + (start / 2); ++i) {
      if (i % 4 == 0 && i != j) {
        if (isspace(game[i])) {
          words.push_back("");
          o += 1;
        }
        words[o] += game[i];
      }
    }
    o += 1;
  }
  for (int i = 0; i < words.size(); ++i) {
    if (words[i][0] == ' ') {
      words[i].erase(0, 1);
    }
    if (has_only_spaces(words[i]) == true || words[i].size() == 0) {
      words.erase(words.begin() + i);
    }
  }
  for (int k = 0; k < words.size(); ++k) {

    if (std::find(v.begin(), v.end(), words[k]) != v.end()) {
      counter += 1;
    }
  }
  if (counter >= v.size()) {
    return true;
  } else {
    counter = 0;
    return false;
  }
}
string Scrambler::display_solution() {
    int moves_made = 1;
    this->game = og_game;
    string solution = str();
    int c = moves.size() - 1;
    while (is_over() != true) {
    if (moves[c][0] == 'c') {
        if (moves[c][2] == 'd') {
        moves[c][2] = 'u';
        } else {
        moves[c][2] = 'd';
        }
        } else {
        if (moves[c][2] == 'r') {
        moves[c][2] = 'l';
        } else {
        moves[c][2] = 'r';
    }
        if (c < 0) {
            break;
        }
    }
    solution += "\n*** Move " + to_string(moves_made) +" (" + string(1, moves[c][0]) + "," + string(1, moves[c][1]) + "," + string(1, moves[c][2]) + ")\n";
    try_move(moves[c]);
    solution += str();
    c -= 1;
    moves_made += 1;
    }
    return solution;
}
vector<string> Scrambler::get_words() const { return v; }
//////////////////////////////////////////////////////////////////////////////////////
int main() {
  srand(1);
  Scrambler new_game("dictionary.txt", 3);
    string display = new_game.display_solution();
    cout << display << endl;
    vector<string> s = new_game.get_words();
    for (string word : s) {
        cout << word << endl;
    }
    cout << new_game.is_over();
    new_game.try_move("r");
    return 0;
}
