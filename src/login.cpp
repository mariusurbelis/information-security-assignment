#include <iostream>
#include <string.h>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "authlib.h"

#define _ ;
#define __ (
#define ___ )
#define ____ int
#define _____ endl
#define ______ ,
#define _______ >>
#define ________ db_line
#define _________ user_name

using namespace std _

const string DB_FILE_NAME = "pwdb.txt" _
vector<array<string ______  2 _______  database _
string  _________  _
string psswd _

/**
 * Source of hash function: 
 * https://stackoverflow.com/questions/13784434/how-to-use-openssls-sha256-functions#1378448
*/
string sha256 __ const string str ___
{
  unsigned char hash[SHA256_DIGEST_LENGTH] _
  SHA256_CTX sha256 _
  SHA256_Init __&sha256 ___ _
  SHA256_Update __&sha256 ______  str.c_str __ ___ ______  str.size __ ___ ___ _
  SHA256_Final __ hash ______  &sha256 ___ _
  stringstream ss _
  for  __ ____ i = 0 _ i < SHA256_DIGEST_LENGTH _ i++ ___
  {
    ss << hex << setw __ 2 ___ << setfill __'0' ___ <<  __ ____ ___ hash[i] _
  }
  return ss.str __ ___ _
}

/**
 * Function that fulfils the role of  ____eracting with user by taking user input 
 */
void usr_input __ ___
{
  cout << "Enter your username" << _____ _
  cin  _______   _________  _
  cout << "Enter your password" << _____ _
  cin  _______  psswd _
  psswd = sha256 __ psswd ___ _
}

/**
 *  db_parse_line function parses an input string
 *  which contains a username and password split
 *  using a colon ":". The username and password
 *  are stored inside a vector called database.
 * 
 *  @param line is the input string
*/
void db_parse_line __ string line ___
{
  istringstream tokenStream __ line ___ _
  vector<string> tokens _
  string token _

  while  __ getline __ tokenStream ______  token ______  ':' ___ ___
    tokens.push_back __ token ___ _

  database.push_back __{tokens[0] ______  tokens[1]} ___ _
}

void import_cred_db __ const string db_file_name ___
{
  ifstream db_file __ db_file_name ___ _
  string  ________  _
  if  __ db_file.is_open __ ___ ___
  {
    while  __ getline __ db_file ______   ________  ___ ___
    {
      db_parse_line __  ________  ___ _
    }
    db_file.close __ ___ _
  }
  else
  {
    cout << "Unable to read password db file" << _____ _
  }
}

 ____ main __ ___
{
  import_cred_db (DB_FILE_NAME);
  usr_input __ ___ _
  for  __ auto i : database ___
  {
    if  __!i[0].compare __  _________  ___ ___
    {
      cout << i[0] << _____
           << i[1] << _____
           << psswd << _____ _
      if  __!i[1].compare __ psswd ___ ___
      {
        authenticated __  _________  ___ _
      }
      else
      {
        rejected __  _________  ___ _
      }
    }
  }
}