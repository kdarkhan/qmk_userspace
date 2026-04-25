#define DYNAMIC_KEYMAP_LAYER_COUNT 7
#define TAPPING_TOGGLE 2
#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 5000

// #define ENCODER_MAP_KEY_DELAY 50
#define EE_HANDS
// #define OLED_UPDATE_INTERVAL 200

#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 120000
#    define OLED_UPDATE_INTERVAL 100
#endif

// homerow mods https://precondition.github.io/home-row-mods
// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 100

#define BILATERAL_COMBINATIONS 500

#define FLOW_TAP_TERM 100

#define CHORDAL_HOLD
