/*
 * Copyright (C) 2005-2008 MaNGOS <http://www.mangosproject.org/>
 *
 * Copyright (C) 2008 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef HELLGROUND_PETAI_H
#define HELLGROUND_PETAI_H

#include "CreatureAI.h"
#include "Timer.h"

class Creature;
class Spell;

class HELLGROUND_DLL_DECL PetAI : public CreatureAI
{
    public:

        explicit PetAI(Creature *c);

        void EnterEvadeMode();
        void JustDied(Unit *who) { _stopAttack(); }

        void UpdateAI(const uint32);
        static int Permissible(const Creature *);

        void AttackStart(Unit *target)
        {
            m_forceTimer = 5000;
            CreatureAI::AttackStart(target);
        }

        virtual void PrepareSpellForAutocast(uint32 spellId);
        virtual void AddSpellForAutocast(uint32 spellId, Unit* target);
        virtual void AutocastPreparedSpells();

        bool targetHasInterruptableAura(Unit *target) const;

    protected:

        void UpdateMotionMaster();

        bool _isVisible(Unit *) const;
        bool _needToStop(void) const;
        void _stopAttack(void);

        void UpdateAllies();

        TimeTracker i_tracker;
        std::set<uint64> m_AllySet;
        uint32 m_updateAlliesTimer;
        uint32 m_forceTimer;

        typedef std::pair<Unit*, Spell*> TargetSpellPair;
        std::vector<TargetSpellPair> m_targetSpellStore;

        Unit* m_owner;              // pointer updated every UpdateAI call
};

class HELLGROUND_DLL_DECL ImpAI : public PetAI
{
    public:
        ImpAI(Creature *c) : PetAI(c), m_chasing(false) {}
        void UpdateAI(const uint32);
        void AttackStart(Unit *);
        static int Permissible(const Creature *);
    protected:
        bool m_chasing;
};

class HELLGROUND_DLL_DECL FelhunterAI : public PetAI
{
    public:
        FelhunterAI(Creature *c) : PetAI(c) {}
        static int Permissible(const Creature *);
        void PrepareSpellForAutocast(uint32 spellId);

};

#endif

