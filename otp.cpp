#include <iostream>
#include <string>
#include <unistd.h>  // For sleep()

int main() {
    std::cout << "You will receive a prompt on your mobile for OTP verification." << std::endl;
    std::cout << "Enter OTP: ";

    std::string otp;
    bool otpEntered = false;

    // Timer countdown, 30 seconds
    for (int i = 30; i >= 0; i--) {
        // If OTP is not entered, check for input
        if (!otpEntered && std::cin.peek() != '\n') {
            std::getline(std::cin, otp);  // Capture OTP input
            if (!otp.empty()) {           // Ensure OTP is not empty
                otpEntered = true;
            }
        }

        // Display the timer on the same line
        std::cout << "\rTime left: " << i << " seconds";
        std::cout.flush();  // Force the output buffer to flush immediately
        
        // If OTP is entered, break out of the loop
        if (otpEntered) {
            break;
        }

        // Wait for 1 second
        sleep(1);
    }

    // If OTP was entered, print it
    if (otpEntered) {
        std::cout << "\nOTP Entered: " << otp << std::endl;
    } else {
        std::cout << "\nTime expired. OTP was not entered in time." << std::endl;
    }

    return 0;
}
