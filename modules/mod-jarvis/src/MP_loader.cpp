/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

// From SC
void AddMyPlayerScripts();
void AddSC_Jarvis_Services();
void AddSC_TestWorld_Boss();

// Add all
// cf. the naming convention https://github.com/azerothcore/azerothcore-wotlk/blob/master/doc/changelog/master.md#how-to-upgrade-4
// additionally replace all '-' in the module folder name with '_' here
void Addmod_jarvisScripts()
{
    AddMyPlayerScripts();
    AddSC_Jarvis_Services();
    AddSC_TestWorld_Boss();
}

