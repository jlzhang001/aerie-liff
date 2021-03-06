/*!
 * @file FluxSource.h
 * @brief Access to properties of sources of particle flux (cosmic rays, gamma
 *        rays, point sources, extended sources).
 * @author Segev BenZvi
 * @date 5 Feb 2015
 * @version $Id: FluxSource.h 27291 2015-10-20 14:19:55Z sybenzvi $
 */

#ifndef GRMODEL_SERVICES_SPECTRA_FLUXSOURCE_H_INCLUDED
#define GRMODEL_SERVICES_SPECTRA_FLUXSOURCE_H_INCLUDED

#include <data-structures/physics/Particle.h>
#include <data-structures/time/ModifiedJulianDate.h>

#include <rng-service/RNGService.h>

class PowerLaw;

/*!
 * @class FluxSource
 * @author Segev BenZvi
 * @date 5 Feb 2015
 * @ingroup gr_models
 * @brief Virtual base class for sources of particles.
 */
class FluxSource {

  public:

    FluxSource() { }

    virtual ~FluxSource() { }

    /// Get the source flux at a given energy
    virtual double GetFlux(const double E, const ModifiedJulianDate& mjd) const = 0;

    /// Get the weight to convert a PowerLaw to this flux
    virtual double GetFluxWeight(const double E, const ModifiedJulianDate& mjd, const PowerLaw& p) const = 0;

    /// Minimum energy (modeled or measured) of particles from the source
    virtual double GetMinEnergy() const = 0;

    /// Maximum energy (modeled or measured) of particles from the source
    virtual double GetMaxEnergy() const = 0;

    /// Randomly sample an energy from the source spectrum in [E0, E1]
    virtual double GetRandomEnergy(const RNGService& rng,
                                   const double E0, const double E1) const = 0;

    /// Integrate the source spectrum between two energies
    virtual double Integrate(const double E0, const double E1,
                             const ModifiedJulianDate& mjd) const = 0;

    /// Get the particle type generated by the source
    const ParticleType& GetParticleType() const
    { return particleType_; }

    const std::string& GetSpectrumServiceName() const
    { return spectrumServiceName_; }

  protected:

    ParticleType particleType_;     ///< Type of particle

    /// Service used to manage the source spectrum (child of CosmicRayService)
    std::string spectrumServiceName_;

};

#endif // GRMODEL_SERVICES_SPECTRA_FLUXSOURCE_H_INCLUDED

