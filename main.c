#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <keyutils.h>

int main() {
    key_serial_t key_id, keyring_id;

    // Creating a key
    key_id = keyctl(KEYCTL_JOIN_SESSION_KEYRING, "my_session_keyring");
    if (key_id < 0) {
        perror("keyctl");
        exit(EXIT_FAILURE);
    }
    printf("Created key ID: %d\n", key_id);

    // Adding a key to a keyring
    keyring_id = keyctl(KEYCTL_JOIN_SESSION_KEYRING, "my_keyring");
    if (keyring_id < 0) {
        perror("keyctl");
        exit(EXIT_FAILURE);
    }
    printf("Created keyring ID: %d\n", keyring_id);

    // Setting expiration time for a key
    int expiry_time = 100; // Set expiry time to 100 seconds
    keyctl(KEYCTL_EXPIRE, key_id, expiry_time);

    // More operations can be performed using keyctl() with various flags
    // ...

    return 0;
}
