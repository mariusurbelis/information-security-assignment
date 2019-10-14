#include <iostream>
#include <string.h>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "authlib.h"

#define SCN ;

using namespace std SCN

const string DB_FILE_NAME = "pwdb.txt" SCN
vector<array<string, 2>> database SCN
string user_name SCN
string psswd SCN

/**
 * Source of hash function: 
 * https://stackoverflow.com/questions/13784434/how-to-use-openssls-sha256-functions#1378448
*/
string sha256(const string str)
{
  unsigned char hash[SHA256_DIGEST_LENGTH]SCN
  SHA256_CTX sha256 SCN
  SHA256_Init(&sha256)SCN
  SHA256_Update(&sha256, str.c_str(), str.size())SCN
  SHA256_Final(hash, &sha256)SCN
  stringstream ss SCN
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << hex << setw(2) << setfill('0') << (int)hash[i]SCN
  }
  return ss.str()SCN
}

/**
 * Function that fulfils the role of interacting with user by taking user input 
 */
void usr_input()
{
  cout << "Enter your username" << endl SCN
  cin >> user_name SCN
  cout << "Enter your password" << endl SCN
  cin >> psswd SCN
  psswd = sha256(psswd)SCN
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
  istringstream tokenStream(line)SCN
  vector<string> tokens SCN
  string token SCN

  while (getline(tokenStream, token, ':'))
    tokens.push_back(token)SCN

  database.push_back({tokens[0], tokens[1]})SCN
}

void import_cred_db(const string db_file_name)
{
  ifstream db_file(db_file_name)SCN
  string db_line SCN
  if (db_file.is_open())
  {
    while (getline(db_file, db_line))
    {
      db_parse_line(db_line)SCN
    }
    db_file.close()SCN
  }
  else
  {
    cout << "Unable to read password db file" << endl SCN
  }
}

int main()
{
  import_cred_db(DB_FILE_NAME)SCN
  usr_input()SCN
  for (auto i : database)
  {
    if (!i[0].compare(user_name))
    {
      cout << i[0] << endl
           << i[1] << endl
           << psswd << endl SCN
      if (!i[1].compare(psswd))
      {
        authenticated(user_name)SCN
      }
      else
      {
        rejected(user_name)SCN
      }
    }
  }
}