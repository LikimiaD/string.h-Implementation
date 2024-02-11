#include "../include/custom_string.h"

custom_size_t custom_strlen(const char *str) {
  custom_size_t count = 0;
  while (str[count] != '\0') {
    count++;
  }
  return count;
}

void *custom_memchr(const void *str, int c, custom_size_t n) {
  if (str == NULL_VALUE) {
    return NULL_VALUE;
  }

  const char *d = (const char *)str;
  while (n--) {
    if (*d == (char)c) {
      return (void *)d;
    }
    d++;
  }
  return NULL_VALUE;
}

void *custom_memset(void *str, int c, custom_size_t n) {
  if (str == NULL_VALUE) {
    return NULL_VALUE;
  }

  char *d = (char *)str;
  while (n--) {
    *d++ = (char)c;
  }
  return str;
}

void *custom_memcpy(void *dest, const void *src, custom_size_t n) {
  if (dest == NULL_VALUE || src == NULL_VALUE) {
    return NULL_VALUE;
  }

  char *d = (char *)dest;
  const char *s = (const char *)src;

  if ((d < s && d + n > s) || (s < d && s + n > d)) {
    return NULL_VALUE;
  }

  char *original_dest = d;
  while (n--) {
    *d++ = *s++;
  }

  return original_dest;
}

int custom_memcmp(const void *str1, const void *str2, custom_size_t n) {
  if (str1 == NULL_VALUE || str2 == NULL_VALUE) {
    return -2;
  }

  const unsigned char *str1_tmp = (const unsigned char *)str1;
  const unsigned char *str2_tmp = (const unsigned char *)str2;

  while (n--) {
    if (*str1_tmp != *str2_tmp) {
      return *str1_tmp - *str2_tmp;
    }
    str1_tmp++;
    str2_tmp++;
  }

  return 0;
}

int custom_strncmp(const char *str1, const char *str2, custom_size_t n) {
  if (str1 == NULL_VALUE || str2 == NULL_VALUE) return -1;

  for (custom_size_t i = 0; i < n && (str1[i] != '\0' || str2[i] != '\0');
       i++) {
    if (str1[i] != str2[i]) {
      return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
  }
  return 0;
}

char *custom_strchr(const char *str, int symbol) {
  char *answer = NULL_VALUE;
  char *ptr = (char *)str;
  while (*ptr != '\0') {
    if (*ptr == symbol) {
      answer = (char *)ptr;
      break;
    }
    ptr++;
  }
  return answer;
}

char *custom_strstr(const char *str1, const char *str2) {
  char *ptr_str1 = (char *)str1;
  char *answer = NULL_VALUE;
  if (*str2 == '\0') {
    answer = ptr_str1;
  } else {
    while (*ptr_str1 != '\0') {
      if (*ptr_str1 == *str2) {
        char *ptr_str2 = (char *)str2;
        char *ptr_local_str1 = ptr_str1;
        custom_size_t status = 0;
        while (*ptr_str2 != '\0') {
          if (*ptr_local_str1 != *ptr_str2) {
            status = 1;
            break;
          }
          ptr_str2++;
          ptr_local_str1++;
        }
        if (status == 0) {
          answer = ptr_str1;
          break;
        }
      }
      ptr_str1++;
    }
  }
  return answer;
}

char *custom_strrchr(const char *str, int symbol) {
  custom_size_t str_len = custom_strlen(str);
  char *answer = NULL_VALUE;

  if (str_len > 0) {
    for (custom_size_t i = str_len; i-- > 0;) {
      if (str[i] == symbol) {
        answer = (char *)&str[i];
        break;
      }
    }
  }

  return answer;
}

char *custom_strtok(char *str, const char *delim) {
  static char *lastToken = NULL_VALUE;
  char *tokenStart = NULL_VALUE;

  if (str == NULL_VALUE) {
    str = lastToken;
  }

  if (str) {
    while (*str && custom_strchr(delim, *str)) {
      str++;
    }

    if (*str) {
      tokenStart = str;
      while (*str && !custom_strchr(delim, *str)) {
        str++;
      }

      if (*str) {
        *str = '\0';
        lastToken = str + 1;
      } else {
        lastToken = str;
      }
    }
  }

  return tokenStart;
}

char *custom_strcpy(char *str1, const char *str2) {
  if (str1 == NULL_VALUE || str2 == NULL_VALUE) return NULL_VALUE;

  custom_size_t i = 0;
  while ((str1[i] = str2[i]) != '\0') {
    i++;
  }
  return str1;
}

char *custom_strncat(char *str1, const char *str2, custom_size_t n) {
  if (str1 == NULL_VALUE || str2 == NULL_VALUE) return NULL_VALUE;

  custom_size_t str1_len = custom_strlen(str1);
  custom_size_t i = 0;
  for (i = 0; i < n && str2[i] != '\0'; i++) {
    str1[str1_len + i] = str2[i];
  }
  str1[str1_len + i] = '\0';
  return str1;
}

char *custom_strncpy(char *str1, const char *str2, custom_size_t n) {
  if (str1 == NULL_VALUE || str2 == NULL_VALUE) return NULL_VALUE;

  custom_size_t i = 0;
  for (i = 0; i < n && str2[i] != '\0'; i++) {
    str1[i] = str2[i];
  }
  for (; i < n; i++) {
    str1[i] = '\0';
  }
  return str1;
}

char *custom_strpbrk(const char *str1, const char *str2) {
  if (str1 == NULL_VALUE || str2 == NULL_VALUE) {
    return NULL_VALUE;
  }

  for (custom_size_t i = 0; str1[i] != '\0'; i++) {
    for (custom_size_t j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        return (char *)(str1 + i);
      }
    }
  }

  return NULL_VALUE;
}

custom_size_t custom_strcspn(const char *str1, const char *str2) {
  if (str1 == NULL_VALUE || str2 == NULL_VALUE) {
    return 0;
  }

  custom_size_t length = 0;

  for (length = 0; str1[length] != '\0'; length++) {
    for (custom_size_t j = 0; str2[j] != '\0'; j++) {
      if (str1[length] == str2[j]) {
        return length;
      }
    }
  }
  return length;
}

// WARNING: Dinamic memory allocated!
void *custom_to_upper(const char *str) {
  if (str == NULL_VALUE) {
    return NULL_VALUE;
  }
  custom_size_t length = custom_strlen(str);
  char *buffer = (char *)malloc(length + 1);
  if (buffer == NULL_VALUE) {
    return NULL_VALUE;
  }
  int count = 0;
  while (str[count] != '\0') {
    if (str[count] >= 'a' && str[count] <= 'z') {
      buffer[count] = (char)(str[count] - ('a' - 'A'));
    } else {
      buffer[count] = str[count];
    }
    count++;
  }
  buffer[count] = '\0';
  return (void *)buffer;
}

custom_size_t custom_strspn(const char *str1, const char *str2) {
  custom_size_t len = 0;
  if (str1 == NULL_VALUE || str2 == NULL_VALUE) {
    return len;
  }
  for (; *str1 != '\0'; str1++) {
    const char *p;
    for (p = str2; *p != '\0' && *p != *str1; ++p) {
    }
    if (*p == '\0') {
      break;
    }
    len++;
  }
  return len;
}

char *custom_strerror(int errnum) {
  static char unknown_error_msg[50];

#if defined(__APPLE__)
#define MAX_ERRLIST 107
#define MIN_ERRLIST -1
#define ERROR "Unknown error "

  static const char *maserror[] = {
      "Undefined error: 0",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "Device not configured",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource deadlock avoided",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Resource busy",
      "File exists",
      "Cross-device link",
      "Operation not supported by device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Result too large",
      "Resource temporarily unavailable",
      "Operation now in progress",
      "Operation already in progress",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol family",
      "Address already in use",
      "Can't assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Socket is already connected",
      "Socket is not connected",
      "Can't send after socket shutdown",
      "Too many references: can't splice",
      "Operation timed out",
      "Connection refused",
      "Too many levels of symbolic links",
      "File name too long",
      "Host is down",
      "No route to host",
      "Directory not empty",
      "Too many processes",
      "Too many users",
      "Disc quota exceeded",
      "Stale NFS file handle",
      "Too many levels of remote in path",
      "RPC struct is bad",
      "RPC version wrong",
      "RPC prog. not avail",
      "Program version wrong",
      "Bad procedure for program",
      "No locks available",
      "Function not implemented",
      "Inappropriate file type or format",
      "Authentication error",
      "Need authenticator",
      "Device power is off",
      "Device error",
      "Value too large to be stored in data type",
      "Bad executable (or shared library)",
      "Bad CPU type in executable",
      "Shared library version mismatch",
      "Malformed Mach-o file",
      "Operation canceled",
      "Identifier removed",
      "No message of desired type",
      "Illegal byte sequence",
      "Attribute not found",
      "Bad message",
      "EMULTIHOP (Reserved)",
      "No message available on STREAM",
      "ENOLINK (Reserved)",
      "No STREAM resources",
      "Not a STREAM",
      "Protocol error",
      "STREAM ioctl timeout",
      "Operation not supported on socket",
      "Policy not found",
      "State not recoverable",
      "Previous owner died",
      "Interface output queue is full"};
#elif defined(__linux__)
#define MAX_ERRLIST 134
#define MIN_ERRLIST -1
#define ERROR "Unknown error "

  static const char *maserror[] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error"};
#endif

  if (errnum > MIN_ERRLIST && errnum < MAX_ERRLIST) {
    return (char *)maserror[errnum];
  } else {
    sprintf(unknown_error_msg, "%s%d", ERROR, errnum);
    return unknown_error_msg;
  }
}