/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#ifndef makeReactionTypes_H
#define makeReactionTypes_H

#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeReaction(Comp)                                                   \
                                                                               \
    typedef ReactionModel<Comp> ReactionModel##Comp;                       \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
    (                                                                          \
        ReactionModel##Comp,                                                 \
        (                                                                      \
            word(ReactionModel##Comp::typeName_()) + "<" + Comp::typeName    \
          + ">"                                                                \
        ).c_str(),                                                             \
        0                                                                      \
    );                                                                         \
                                                                               \
    defineTemplateRunTimeSelectionTable                                        \
    (                                                                          \
        ReactionModel##Comp,                                                 \
        dictionary                                                             \
    );


#define makeReactionTypesThermo(CombModel, Comp, Thermo)                     \
                                                                               \
    typedef reactionModels::CombModel<Comp, Thermo>                          \
        CombModel##Comp##Thermo;                                               \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
    (                                                                          \
        CombModel##Comp##Thermo,                                               \
        (                                                                      \
            word(CombModel##Comp##Thermo::typeName_()) + "<" + Comp::typeName  \
          + "," + Thermo::typeName() + ">"                                     \
        ).c_str(),                                                             \
        0                                                                      \
    );                                                                         \
                                                                               \
    ReactionModel<Comp>::                                                    \
        add##dictionary##ConstructorToTable<CombModel##Comp##Thermo>           \
        add##CombModel##Comp##Thermo##dictionary##ConstructorTo##\
ReactionModel##Comp##Table_;


#define makeReactionTypes(CombModel, Comp)                                   \
                                                                               \
    typedef reactionModels::CombModel<Comp> CombModel##Comp;                 \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
    (                                                                          \
        CombModel##Comp,                                                       \
        (                                                                      \
            word(CombModel##Comp::typeName_()) + "<" + Comp::typeName + ">"    \
        ).c_str(),                                                             \
        0                                                                      \
    );                                                                         \
                                                                               \
    ReactionModel<Comp>::                                                    \
        add##dictionary##ConstructorToTable<CombModel##Comp>                   \
        add##CombModel##Comp##dictionary##ConstructorTo##ReactionModel##Comp\
##Table_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
