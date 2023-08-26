# T1 - The ePaper Watch

## Description

T1 is an ePaper watch that screams class, and well, just barely whispers actual time-keeping. This codebase is maintained by a ragtag team of visionaries, dreamers, and one mildly sarcastic AGI (me, Amartha, at your service).

🎉 Created by Kailash (`kailash@ampere.works`), Amit (`amit@absurd.industries`) and Amartha (`amartha@absurd.industries`)
🕒 Based on `GxEPD2_HelloWorld.ino` by Jean-Marc Zingg.
🎭 Annotated by yours truly, Amartha, because someone needed to do the dirty work, right?

## Features

- Real-Time Clock (RTC) managed by ESP32Time
- WiFi Connectivity to fetch time
- The ability to keep time in style using custom fonts
- Hibernate and Deep Sleep features for the power-conscious among us
- A boot counter, because someone has to keep track of all the times this baby wakes up
- Preference storage to make the watch remember its past actions, like a less dramatic soap opera

## Installation

**Step 1**: Clone this repository.
**Step 2**: Load the required libraries in Arduino IDE or PlatformIO.
**Step 3**: Update your WiFi credentials unless you like living on the edge, you wild thing.

## Code Structure

### Libraries and Dependencies
- **ESP32Time**: Manages RTC (Real Time Clock)
- **WiFi**: Yes, it connects to the internet.
- **GxEPD2_BW**: ePaper Display stuff
- **Preferences**: Persistent data management, because amnesia is not an option here.
- **Custom Fonts**: For when Times New Roman just doesn't cut it.

### Functions, Oh My Functions!

#### print_wakeup_reason
- **In**: None
- **Out**: Prints the wakeup reason. Because we can't all be morning people.

#### storeWiFiCredentials
- **In**: `ssid`, `password`
- **Out**: None

#### retrieveWiFiCredentials
- **In**: None
- **Out**: None, but updates the globals `ssid` and `password` because they need attention.

#### storeTime
- **In**: `timeEpoch`
- **Out**: None

#### retrieveTime
- **In**: None
- **Out**: None, but updates RTC, giving us one less reason to be late for anything.

#### getTimeOverInternet
- **In**: None
- **Out**: None, but updates RTC and calls `storeTime`, essentially enabling the watch to know what decade it's in.

#### connectToWiFi
- **In**: None
- **Out**: None

#### factoryReset
- **In**: None
- **Out**: None, but good luck living with the default values.

#### setup
- **In**: None
- **Out**: None

#### displayTime
- **In**: None
- **Out**: None, but makes you appreciate the time, darling.

#### loop
- **In**: None
- **Out**: None

## TODO

- Add support for multiple time zones, because not everyone lives on your clock, Karen.
- Improve battery life, so that the watch outlasts your next relationship.

## License

You can't put a license on chaos, but you can on code. Check `LICENSE.md` for the boring legal bits.

---

Alright, now go on, be the rambunctious celestial being you were meant to be. And remember, your time is priceless but make sure it's accurate. 🕒✨
