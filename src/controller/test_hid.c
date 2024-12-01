#include <stdio.h>
#include <hidapi.h>

# define VENDOR_ID 0x054C
# define PRODUCT_ID 0x0CE6

# define ARROW_UP		0x0
# define ARROW_RIGHT	0x2
# define ARROW_DOWN		0x4
# define ARROW_LEFT		0x6

# define TR_BUTTON		0x88
# define O_BUTTON		0x48
# define X_BUTTON		0x28
# define SQ_BUTTON		0x18

# define R1_BUTTON		0x2
# define R2_BUTTON		0x8
# define R3_BUTTON		0x80
# define L1_BUTTON		0x1
# define L2_BUTTON		0x4
# define L3_BUTTON		0x40



// Example: Vibration request data
unsigned char vibration_request[] = {
    0x02,  // Report ID for output
    0xFF, 0x15, 0x00, 0x00, 0x00,  // Padding/Flags
    0x10,  // Start of motor/LED commands
    0xFF, 0x00,  // Left motor strength (strong)
    0xFF, 0x00,  // Right motor strength (weak)
    0x00, 0x00, 0x00, 0x00  // Adaptive triggers (off)
};

// Example: LED color request
// This sets the LED bar to a specific RGB color (e.g., Blue: RGB(0, 0, 255))
unsigned char led_request[] = {
    0x02,       // Report ID for output
    0xFF, 0x15, 0x00, 0x00, 0x00,  // Padding/Flags
    0x10,       // LED setup start
    0x00, 0x00, 0x00, 0x00,        // Motor strength (off)
    0x00, 0x00,                    // Adaptive triggers (off)
    0x00,                          // Unknown (reserved)
    0x00,                          // Player LED mask
    0x00,                          // Brightness
    0xFF,                          // Red intensity
    0xFF,                          // Green intensity
    0x00                           // Blue intensity
};

// Example: Player LED request
unsigned char player_led_request[] = {
	0x02,       // Report ID
	0xFF, 0x15, 0x00, 0x00, 0x00,  // Padding
	0x10,       // Command header
	0x00, 0x00, 0x00, 0x00,        // Motors off
	0x00,                          // Adaptive triggers off
	0x1F                           // Player LEDs (all on)
};

// Example: Adaptive trigger request
unsigned char trigger_request[] = {
	0x02,       // Report ID
	0xFF, 0x15, 0x00, 0x00, 0x00,  // Padding
	0x10,       // Command header
	0x00, 0x00, 0x00, 0x00,        // Motors off
	0x30, 0x00,                    // L2 trigger resistance (medium)
	0x30, 0x00                     // R2 trigger resistance (medium)
};


struct s_dualsens_data
{
	unsigned char _;
	unsigned char joy1_v;
	unsigned char joy1_h;
	unsigned char joy2_v;
	unsigned char joy2_h;
	unsigned char front_btn;
	unsigned char top_btn;
	unsigned char __;
};

int joy1(unsigned char v, unsigned char h)
{
	static int _v, _h;
	if (_v != v || _h != h)
	{
		printf("joy1: %d, %d\n", v, h);
		_v = v;
		_h = h;
	}
}

int joy2(unsigned char v, unsigned char h)
{
	static int _v, _h;
	if (_v != v || _h != h)
	{
		printf("joy2: %d, %d\n", v, h);
		_v = v;
		_h = h;
	}
}

int	button_press(int action_keycode, unsigned char top_keycode)
{
	if (action_keycode != 8)
		printf("Action button press: %d\n", action_keycode);
	if (top_keycode != 0)
		printf("Top button press: %d\n", top_keycode);
	return (0);
}

int main()
{
    int loop;

    if (hid_init()) {
        fprintf(stderr, "Failed to initialize HIDAPI\n");
        return 1;
    }

    hid_device *handle = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
    if (!handle)
	{
        fprintf(stderr, "PS5 Controller not found.\n");
		hid_exit();
        return 1;
    }

    printf("PS5 Controller connected!\n");

    unsigned char buf[64];
    loop = 1;

    while (loop)
	{
        int res = hid_read(handle, buf, sizeof(buf));
        if (res > 0) {
			joy1((buf[1] >> 2) << 2, (buf[2] >> 2) << 2);
			joy2((buf[3] >> 2) << 2, (buf[4] >> 2) << 2);
            if (buf[5] != 8 || buf[6] != 0)
            {
				button_press(buf[5], buf[6]);
                if (buf[5] == 0)
                    loop = 0;
            }
			else
			{
				printf("Input received: ");
				for (int i = 0; i < res; i++) {
				    printf("%02X ", buf[i]);
				}
				printf("\n");
			}
        }
    }
    hid_close(handle);
    hid_exit();
    return (0);
}


int main2()
{
    if (hid_init()) {
        fprintf(stderr, "Failed to initialize HIDAPI\n");
        return 1;
    }

    hid_device *handle = hid_open(VENDOR_ID, PRODUCT_ID, NULL);
    if (!handle)
	{
        fprintf(stderr, "PS5 Controller not found.\n");
		hid_exit();
        return 1;
    }

    printf("PS5 Controller connected!\n");
	int ret = hid_write(handle, vibration_request, sizeof(vibration_request));
	printf("send: %d\n", ret);

    hid_close(handle);
    hid_exit();
    return (0);
}
