const unsigned int ledPin = 13;                                    // My Teensy has the built-in LED on pin 13.

void setup()
{
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    hurryUp();                                                     // Fucking drivers.
    spawnReverseTCP();                                             // This gets our shell.
}

void loop()                                                        // This is a one-off program. Looping is irrelevant.
{
}

void hurryUp()                                                     // Wait for the driver to finish installing.
{
    boolean areWeThereYet = capsCheck();                           // Check and see if we can turn on Caps Lock yet.
    while (areWeThereYet == capsCheck())                           // Spam the shit out of it if not.
    {
        returnCode(1, 500);
        hitCaps();
    }
    hitCaps();
}

boolean capsCheck()                                                // Check if Caps Lock is on.
{
    if ((activeLEDs() & 2) == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

unsigned int activeLEDs()                                          // Keyboard LED status.
{
    return int(keyboard_leds);
}

void returnCode(unsigned int numBlinks, unsigned int halfDelay)
{
    unsigned int count=0;
    for(count = 0; count != numBlinks; count++)
    {
        digitalWrite(ledPin, HIGH);
        delay(halfDelay);
        digitalWrite(ledPin, LOW);
        delay(halfDelay);
    }
}

void hitCaps()                                                     // Press the Caps Lock button.
{
    Keyboard.set_key1(KEY_CAPS_LOCK);
    Keyboard.send_now();
    delay(100);
    clearKeys();
}

void clearKeys()                                                   // Empty the keystroke buffer.
{
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    delay(100);
}

void killCaps()                                                    // Turn off Caps Lock.
{
    if (capsCheck())
    {
        hitCaps();
    }
}

void spawnReverseTCP()                                             // Start the real magic.
{
    killCaps();                                                    // Turn off Caps Lock if it's on.
    
    returnCode(1, 100);                                            // Keyboard is ready.
    
    Keyboard.set_modifier(MODIFIERKEY_RIGHT_GUI);                  // Open the Run dialog.
    Keyboard.set_key1(KEY_R);
    Keyboard.send_now();
    clearKeys();
    
    delay(1000);
    
    returnCode(1, 100);                                            // Run is ready.
    // this can be changed to anylink
    Keyboard.print("iexplore.exe -k https://www.youtube.com/watch?v=oHg5SJYRHA0"); 
    Keyboard.set_key1(KEY_ENTER);
    Keyboard.send_now();
    clearKeys();                                      // All done.
}
