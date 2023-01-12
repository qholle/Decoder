#include "enigma.h"

const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void Get_Message(char msg[]){
    scanf("%[^\n]%*c", msg);
    return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[]){
    scanf("%s", which_rotors);
    int rotorCount = 0;
    while(which_rotors[rotorCount] != '\0'){
        rotorCount++;
    }
    return rotorCount;
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int Get_Rotations(){
    int rotations = -1;
    scanf("%d", &rotations);
    return rotations;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]){
    int i = 0;
    int j;
    while(which_rotors[i]){
        j = 0;
        while(j != 27){
            encryption_rotors[i][j] = ROTOR_CONSTANTS[which_rotors[i]-48][j];
            j++;
        }
        i++;
    }
    return;
}


// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27]) {
    int i = 0;
    int j;
    char tempRotor[27];

    while(encryption_rotors[i][0] >= 'A' || encryption_rotors[i][0] >= 'Z' || encryption_rotors[i][0] >= ' '){
        for (j = 0; j < 26; j++){
            tempRotor[j] = encryption_rotors[i][j];
        }
        for (j = 0; j < rotations; j++){
            encryption_rotors[i][j] = tempRotor[26-rotations+j];
        }
        for (j = 0; j < (26-rotations); j++){ 
            encryption_rotors[i][j+rotations] = tempRotor[j];
        }
        i++;
    }
    return;
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]){
    int i = 0;
    int j = 0;
    int k = 0;

    //copying msg to encrypted_msg to start
    while(msg[i] != '\0'){
        encrypted_msg[i] = msg[i];
        i++;
    }
    encrypted_msg[i] = '\0'; //append \0 to end of string

    //encrypt the message num_active_rotors times
    for(i = 0; i < num_active_rotors; i++){
        j = 0;
        //find the character in the same array position as encrypted_msg[j] in the correct encryption rotor 
        while(encrypted_msg[j] != '\0'){ 
            if(encrypted_msg[j] != ' '){
                k = 0;
                while(encrypted_msg[j] != ROTOR_CONSTANTS[0][k]){
                    k++;
                }
                encrypted_msg[j] = encryption_rotors[i][k];
            }
            j++;
        }
    }
    return;
}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
    int i = 0;
    int j = 0;
    int k = 0;

    while(encrypted_msg[i] != '\0'){
        decrypted_msg[i] = encrypted_msg[i];
        i++;
    }
    decrypted_msg[i] = '\0'; //append \0 to end of string

    //decrypt the message num_active_rotors times
    for(i = num_active_rotors-1; i >= 0; i--){
        j = 0;
        
        //find the character in the same array position as decrypted_msg[j] in the correct encryption rotor 
        while(decrypted_msg[j] != '\0'){ 
            if(decrypted_msg[j] != ' '){
                k = 0;
                while(decrypted_msg[j] != encryption_rotors[i][k]){
                    k++;
                }
                decrypted_msg[j] = ROTOR_CONSTANTS[0][k];
            }
            j++;
        }
    }

    return;
}


