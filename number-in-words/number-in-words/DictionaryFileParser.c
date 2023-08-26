//
//  DictionaryFileParser.c
//  number-in-words
//
//  Created by Tester on 27.8.2023.
//

#include "DictionaryFileParser.h"

#include "StringToNumber.h"

#include <fcntl.h> // open
#include <errno.h> // errno
#include <unistd.h> // close
#include <stdlib.h> // malloc

int isPrintableChar(char ch)
{
    if (ch >= '0' && ch <= '9') {
        return 1;
    }
    
    if (ch >= 'A' && ch <= 'Z') {
        return 1;
    }
    
    if (ch >= 'a' && ch <= 'z') {
        return 1;
    }
    
    if (ch == ' ' || ch == '!') {
        return 1;
    }
    return 0;
}

void copyString(const char *src, char *dst)
{
    while (*src != '\0') {
        *dst = *src;
        ++src;
        ++dst;
    }
    *dst = '\0';
}

//void xxxx(void)
//{
//    if (*keyFound == 0) {
//        if (bytesCopied != 0) {
//            int errCode = numberForString(numericString, keyp);
//            if (errCode != 0) {
//                return EINVAL;
//            }
//            *keyFound = 1;
//        }
//        else {
//            return EINVAL;
//        }
//    }
//}

int getKeyStringFromFd(int fd, int *eofp, char *key, ssize_t keySize)
{
    int ok = 1;
    
    ssize_t bytesCopied = 0u;
    int spaceStarted = 0;
    int col = 1;
    
    while (ok) {
        char ch;
        ssize_t bytesRead = read(fd, &ch, sizeof(ch));
        if (bytesRead < 0) {
            return errno;
        }
        if (bytesRead == 0) {
            // end of file
            *eofp = 1;
            if (bytesCopied != 0) {
                return EINVAL;
            }
            return 0;
        }
        
        if (col == 1) {
            if (!(ch >= '0' && ch <= '9') && (ch != '\n')) {
                return EINVAL;
            }
            ++col;
        }
        
        if (spaceStarted == 1) {
            if ((ch != ' ') && (ch != ':')) {
                return EINVAL;
            }
        }
        
        if (ch == '\n') {
            return 0;
        }
        
        if ((ch >= '0' && ch <= '9')) {
            if (bytesCopied == (keySize-1)) {
                return EINVAL;
            }
            key[bytesCopied] = ch;
            ++bytesCopied;
            key[bytesCopied] = '\0';
        }
        else if (ch == ' ') {
            spaceStarted = 1;
            continue;
        }
        else if (ch == ':') {
            break;
        }
        else {
            return EINVAL;
        }
    }
    
    return 0;
}

int getValueFromFd(int fd, int *eofp, char **valuep)
{
    int ok = 1;
    
    const ssize_t allocSize = 256;
    ssize_t bytesCopied = 0u;
    ssize_t bytesAllocated = 0u;
    
    while (ok) {
        char ch;
        ssize_t bytesRead = read(fd, &ch, sizeof(ch));
        if (bytesRead < 0) {
            return errno;
        }
        if (bytesRead == 0) {
            // end of file
            *eofp = 1;
            
            if (bytesCopied == 0) {
                return EINVAL;
            }
            
            return 0;
        }
        
        if (ch == '\n') {
            if (bytesCopied == 0) {
                return EINVAL;
            }
            (*valuep)[bytesCopied] = '\0';
            return 0;
        }
        
        if (ch == ' ' && bytesCopied == 0) {
            continue;
        }
        
        if (0 == isPrintableChar(ch)) {
            return EINVAL;
        }
        
        if (*valuep == NULL) {
            *valuep = malloc(allocSize);
            bytesAllocated += allocSize;
        }
        if ((bytesCopied-1) == bytesAllocated) {
            (*valuep)[bytesCopied] = '\0';
            char *newp = malloc(bytesAllocated+allocSize);
            copyString(*valuep, newp);
            free(*valuep);
            *valuep = newp;
            bytesAllocated += allocSize;
        }
        
        (*valuep)[bytesCopied] = ch;
        ++bytesCopied;
    }
    return 0;
}

int buildKeyValueFromFd(int fd, int *eofp)
{
    int errCode = 0;
    
    const ssize_t keySize = 3;
    char numericStringKey[keySize];
    
    unsigned long long key;
    
    char *value = NULL;
    
    while ((errCode == 0) && (*eofp == 0) ) {
        errCode = getKeyStringFromFd(fd, eofp, numericStringKey, keySize);
        if (errCode != 0) {
            break;
        }
        errCode = numberForString(numericStringKey, &key);
        if (errCode != 0) {
            break;
        }
        errCode = getValueFromFd(fd, eofp, &value);
    }
    
    return 0;
}

int buildDictionaryFromFd(int fd)
{
    int eof = 0;
    int errCode = 0;
    
    while ((errCode == 0) && (eof == 0)) {
        errCode = buildKeyValueFromFd(fd, &eof);
    }
    
    return 0;
}

int buildDictionaryFromFile(const char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        return errno;
    }
    int errCode = buildDictionaryFromFd(fd);
    close(fd);
    return errCode;
    
    return 0;
}
