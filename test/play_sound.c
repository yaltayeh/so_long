#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define PCM_DEVICE "/dev/snd/pcmC0D0p" // Example PCM device, check your system for the correct one
#define BUFFER_SIZE 1024

int main() {
    int pcm_fd, file_fd;
    unsigned char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Open the PCM device for writing (output)
    pcm_fd = open(PCM_DEVICE, O_WRONLY);
    if (pcm_fd == -1) {
        perror("Error opening PCM device");
        return -1;
    }

    // Open the audio file (raw PCM data or WAV file)
    file_fd = open("sound.wav", O_RDONLY);
    if (file_fd == -1) {
        perror("Error opening audio file");
        close(pcm_fd);
        return -1;
    }

    // Read the audio file and write it to the PCM device
    while ((bytes_read = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(pcm_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to PCM device");
            close(file_fd);
            close(pcm_fd);
            return -1;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading audio file");
    }

    // Clean up
    close(file_fd);
    close(pcm_fd);

    printf("Finished playing sound\n");
    return 0;
}
