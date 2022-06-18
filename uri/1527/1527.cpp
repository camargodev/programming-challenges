#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>

using namespace std; 

class Guilds {
  public:
    long *guildRoots;
    long *guildsSizes;
    bool *isMainGuilds;
    long *guildPowers;

    Guilds(int numberOfPlayers) { 
        this->guildRoots = new long[numberOfPlayers];
        this->guildsSizes = new long[numberOfPlayers];
        this->isMainGuilds = new bool[numberOfPlayers];
        this->guildPowers = new long[numberOfPlayers];
        for (int i = 0; i < numberOfPlayers; i++) {
            this->guildRoots[i] = i;
            this->guildsSizes[i] = 1;  
            this->isMainGuilds[i] = false;
        }
    }
    ~Guilds() { delete[] guildRoots; delete[] guildsSizes; delete[] isMainGuilds; }

    void updateRoots(long guild, long root) {
        while (guild != root) {
            int newGuild = this->guildRoots[guild];
            this->guildRoots[guild] = root;
            guild = newGuild;
        }
    }

    // To which root the bank belongs?
    // All banks on a fusion always same the same root
    long getFusionRoot(long guild) {
        long fusionRoot = guild;
        while (fusionRoot != this->guildRoots[fusionRoot])
            fusionRoot = this->guildRoots[fusionRoot];

        this->updateRoots(guild, fusionRoot);
        return fusionRoot;
    }

    bool areBanksFusioned(long guild1, long guild2) {
        // two banks are fusioned if they have the same root
        return getFusionRoot(guild1) == getFusionRoot(guild2);
    }

    // Replace sets containing x and y with their union.
    void fusionBanks(long guild1, long guild2) {
        long guildRoot1 = getFusionRoot(guild1);
        long guildRoot2 = getFusionRoot(guild2);
        
        // if they are already fusioned
        if (guildRoot1 == guildRoot2)
            return;
        
        // both banks should point to the same root
        this->guildRoots[guildRoot1] = guildRoot2;
        this->guildsSizes[guildRoot2] += this->guildsSizes[guildRoot1];
        this->guildPowers[guildRoot2] += this->guildPowers[guildRoot1];
        if (this->isMainGuilds[guildRoot1])
            this->isMainGuilds[guildRoot2] = true;
        if (this->isMainGuilds[guildRoot2])
            this->isMainGuilds[guildRoot1] = true;
    }

    void printGuild(long guild) {
        cout << "I'm guild " << guild << " with root " << guildRoots[guild] << endl;
        cout << "  My guild size is " << guildsSizes[guild] << " with power " << guildPowers[guild];
        cout << " and part of main: " << isMainGuilds[guild] << endl;
    }
};

int main() {

    int numPlayers, numActions;
    while(true) {
        cin >> numPlayers >> numActions;
        if (numPlayers == 0 && numPlayers == 0)
            break;
        
        Guilds guilds(numPlayers);
        guilds.isMainGuilds[0] = true;

        for (int i = 0; i < numPlayers; i++) {
            int power; cin >> power;
            guilds.guildPowers[i] = power;
            // guilds.printGuild(i);
        }

        int mainGuildWins = 0;

        for (int i = 0; i < numActions; i++) {
            int action, guild1, guild2;
            cin >> action >> guild1 >> guild2;
            guild1--; guild2--;
            if (action == 1) {
                guilds.fusionBanks(guild1, guild2);
            } else {
                long guild1Root = guilds.getFusionRoot(guild1);
                long guild2Root = guilds.getFusionRoot(guild2);
                bool isGuild1Main = guilds.isMainGuilds[guild1Root];
                bool isGuild2Main = guilds.isMainGuilds[guild2Root];
                long guild1TotalPower = guilds.guildPowers[guild1Root];
                long guild2TotalPower = guilds.guildPowers[guild2Root];
                if (isGuild1Main && (guild1TotalPower > guild2TotalPower))
                    mainGuildWins += 1;
                if (isGuild2Main && (guild2TotalPower > guild1TotalPower))
                    mainGuildWins += 1;
            }
        }

        cout << mainGuildWins << endl;
    }
}