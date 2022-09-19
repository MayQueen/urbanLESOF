/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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

Class
    Foam::reactionModel

Description
    Base class for reaction models

SourceFiles
    reactionModel.C

\*---------------------------------------------------------------------------*/

#ifndef reactionModel_H
#define reactionModel_H

#include "IOdictionary.H"
#include "turbulentFluidThermoModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                     Class reactionModel Declaration
\*---------------------------------------------------------------------------*/

class reactionModel
:
    public IOdictionary
{
    // Private Member Functions

        //- Construct the base IO object
        IOobject createIOobject
        (
            basicThermo& thermo,
            const word& reactionProperties
        ) const;


protected:

    // Protected data

        //- Reference to the mesh database
        const fvMesh& mesh_;

        //- Reference to the turbulence model
        const compressibleTurbulenceModel& turb_;

        //- Dictionary of the model
        dictionary coeffs_;

        //- Model type
        const word modelType_;


public:

    //- Runtime type information
    TypeName("reactionModel");

    //- Default reactionProperties dictionary name
    static const word reactionPropertiesName;


    // Constructors

        //- Construct from components
        reactionModel
        (
            const word& modelType,
            basicThermo& thermo,
            const compressibleTurbulenceModel& turb,
            const word& reactionProperties=reactionPropertiesName
        );

        //- Disallow default bitwise copy construction
        reactionModel(const reactionModel&);


    // Selectors

        //- Generic New for each of the related chemistry model
        template<class CombustionModel>
        static autoPtr<CombustionModel> New
        (
            typename CombustionModel::reactionThermo& thermo,
            const compressibleTurbulenceModel& turb,
            const word& reactionProperties
        );


    //- Destructor
    virtual ~reactionModel();


    // Member Functions

        //- Return const access to the mesh database
        inline const fvMesh& mesh() const;

        //- Return access to turbulence
        inline const compressibleTurbulenceModel& turbulence() const;

        //- Return const access to rho
        inline const volScalarField& rho() const;

        //- Return const access to phi
        inline tmp<surfaceScalarField> phi() const;

        //- Return const dictionary of the model
        inline const dictionary& coeffs() const;

        //- Correct reaction rate
        virtual void correct() = 0;

        //- Fuel consumption rate matrix, i.e. source term for fuel equation
        virtual tmp<fvScalarMatrix> R(volScalarField& Y) const = 0;

        //- Heat release rate [kg/m/s^3]
        virtual tmp<volScalarField> Qdot() const = 0;

        //- Update properties from given dictionary
        virtual bool read();


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const reactionModel&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "reactionModelI.H"

#ifdef NoRepository
    #include "reactionModelTemplates.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
