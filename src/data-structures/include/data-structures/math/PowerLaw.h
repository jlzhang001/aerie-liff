/*!
 * @file PowerLaw.h
 * @brief Representation of a power law function.
 * @author Segev BenZvi
 * @date 10 Jan 2011
 * @version $Id: PowerLaw.h 14879 2013-04-27 16:21:17Z sybenzvi $
 */

#ifndef DATACLASSES_MATH_POWERLAW_H_INCLUDED
#define DATACLASSES_MATH_POWERLAW_H_INCLUDED

#include <hawcnest/processing/Bag.h>

#include <hawcnest/HAWCUnits.h>

/*!
 * @class PowerLaw
 * @ingroup math
 * @author Segev BenZvi
 * @date 10 Jan 2011
 * @brief Class which encapsulates a power law, and allows data generated by
 *        one power law to be reweighted into another kind of power law
 * @todo Check for domain errors when evaluating the power law at some x?
 *
 * @author Tom Weisgarber
 * @date 13 November 2012
 * @brief Changed integral to use GetNormWeight, changed the reweighting
 *        scheme to give the correct normalization (assuming that events
 *        being reweighted were sampled from a power law with integral 1),
 *        and updated GetNormWeight to account for spectral indices of -1.
 *
 * This class defines a power law function of form
 * \f[
 *   f(x) = A\cdot \left(\frac{x}{x_N}\right)^{\gamma},
 * \f]
 * where the input \f$ x \f$ is defined over the domain \f$ [x_0, x_1] \f$.
 * Note the sign convention of the spectral index must be given by the user.
 * I.e., if an \f$ x^{-2} \f$ power law is desired, the user must pass an
 * argument -2 to the constructor.
 *
 * The class provides a normalization function that allows this PowerLaw to be
 * reweighted into another PowerLaw.  If the upper limit is infinite
 * the normalization constant is given by
 * \f[
 *   A = -(\gamma+1)\cdot x_N^\gamma \cdot x_0^{-(\gamma + 1)}
 * \f]
 * The minus sign comes in because of the sign convention we have chosen for
 * the spectral index.  The normalization assumes that the integral of the
 * power law converges on \f$ [x_0,\infty) \f$, which means that 
 * \f$ \gamma \leq -1 \f$ in this case.
 *
 * Alternatively, if the upper limit is finite the normalization constant is
 * given by
 * \f[
 *  A = \frac{x_N^\gamma(\gamma+1)}{x_1^{\gamma+1} - x_0^{\gamma+1}}
 * \f]
 */
class PowerLaw : public Baggable {

  public:

    PowerLaw();

    PowerLaw(const double x0, const double x1,
             const double A, const double xN, const double i);

    virtual ~PowerLaw() { }

    /// Get the normalization constant A of the power law
    double GetNormalization() const { return A_; }

    /// Get the location where the normalization constant is defined
    double GetNormX() const { return xN_; }

    /// Get the minimum valid input of the power law
    double GetMinX() const { return x0_; }

    /// Get the maximum valid input of the power law
    double GetMaxX() const { return x1_; }

    /// Return the power law spectral index as a function of x
    virtual double GetSpectralIndex(const double x=0) const { return idx1_; }

    /// Evaluate the power law at some value
    virtual double Evaluate(const double x) const;

    /// Evaluate the integral of the power law
    virtual double Integrate(const double x0,
                             const double x1=HAWCUnits::infinity) const;

    /// Get the factor or "weight" needed to normalize the integral of the
    /// power law between x0 and infinity
    virtual double GetNormWeight(const double x0,
                                 const double x1=HAWCUnits::infinity) const;

    /// Reweight a value x from another power law to obey this power law
    virtual double Reweight(const PowerLaw& pl, const double x) const;

    /// Get the probability to keep an event sampled from some other power
    /// law so that it obeys this power law
    virtual double GetProbToKeep(const PowerLaw& pl, const double x) const;

    /// Get number of transition points in the spectrum (including bounds)
    virtual unsigned int GetNEdges() const { return 2; }

    /// Get the x-value of transition idx
    virtual double GetEdgeX(unsigned int idx) const;

    /// Get the value of x between x0 and x1 at which the integral obtains
    /// some fraction of its total value
    virtual double InvertIntegral(const double frac) const;

  protected:

    double x0_;     ///< Minimum x 
    double x1_;     ///< Maximum x
    double A_;      ///< Power law normalization
    double xN_;     ///< Location x where normalization is defined
    double idx1_;   ///< Spectral index

};

SHARED_POINTER_TYPEDEFS(PowerLaw);

#endif // DATACLASSES_MATH_POWERLAW_H_INCLUDED

