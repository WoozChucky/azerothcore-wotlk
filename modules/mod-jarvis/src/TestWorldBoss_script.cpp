#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Log.h"

enum Spells
{
    SPELL_CLEAVE = 15284,
    SPELL_ENRAGE = 27680
};

class TestWorld_Boss : public CreatureScript
{
public:
    TestWorld_Boss() : CreatureScript("TestWorldBoss_script") { } // script name onto the DB

    struct World_BossAI : public ScriptedAI
    {

        World_BossAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 spell_cleave_timer;
        uint32 Spawn_Timer;
        bool enraged;
        uint32 addsDespawnTime = 1000;

        void EnterCombat(Unit* /*who*/) override
        {
            Spawn_Timer = 5000; //5sec
            spell_cleave_timer = 10000; //10sec
            enraged = false;
            Talk(0);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;
            if(spell_cleave_timer <= diff)
            {
                SpellCastResult cleaveResult = DoCastVictim(SPELL_CLEAVE);
                if (cleaveResult == SPELL_CAST_OK) {
                    LOG_INFO("server.worldserver", "Did hit cleave (SPELL_CAST_OK)");
                }
                spell_cleave_timer = 10000;
            }
            else
                spell_cleave_timer -= diff;

            if(Spawn_Timer <= diff)
            {
                float x = me->GetPositionX();
                float y = me->GetPositionY();
                float z = me->GetPositionZ();
                DoSpawnCreature(15644, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, addsDespawnTime);
                LOG_INFO("server.worldserver", "Spawned add at (%f, %f, %f)", x, y, z);

                Spawn_Timer = 5000;
            }
            else
                Spawn_Timer -= diff;

            if(HealthBelowPct(20) && !enraged)
            {
                DoCast(me,SPELL_ENRAGE);
                enraged = true;
            }
            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new World_BossAI(creature);
    }
};

void AddSC_TestWorld_Boss()
{
    new TestWorld_Boss();
}
