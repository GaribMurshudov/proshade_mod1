/*! \file simpleAccess_distances.cpp
    \brief This file demonstrates how the simple access shape distances ProSHADE run can be done using the ProSHADE dynamic library.

    The code shown here demonstrates how the ProSHADE tool can be used in the simple access mode. Note that the simple access mode does not require any user knowledge of the inner workings of ProSHADE
    except for knowing the settings and the values they would like to use; it only requires the user to fill in the settings object and then run proshade. There is also the advanced access interface, which is shown in a
    different file. The code here  shows how the ProSHADE shape distances can be computed and how they can be programatically accessed. 

    Copyright by Michal Tykac and individual contributors. All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
    1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    3) Neither the name of Michal Tykac nor the names of this code's contributors may be used to endorse or promote products derived from this software without specific prior written permission.

    This software is provided by the copyright holder and contributors "as is" and any express or implied warranties, including, but not limitted to, the implied warranties of merchantibility and fitness for a particular purpose are disclaimed. In no event shall the copyright owner or the contributors be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limitted to, procurement of substitute goods or services, loss of use, data or profits, or business interuption) however caused and on any theory of liability, whether in contract, strict liability or tort (including negligence or otherwise) arising in any way out of the use of this software, even if advised of the possibility of such damage.

    \author    Michal Tykac
    \author    Garib N. Murshudov
    \version   0.7.3
    \date      JUL 2020
*/

//==================================================== ProSHADE
#include "../../src/proshade/ProSHADE.hpp"

//==================================================== Main
int main ( int argc, char **argv )
{
    //================================================ Create the settings object and parse the command line arguments
    ProSHADE_Task task                                = Distances;                           // Setting the task ahead sets most of the default settings to best values for the task.
    ProSHADE_settings* settings                       = new ProSHADE_settings ( task );      // Creating the ProSHADE_settings object, which caries all of the settings and where everything can be set.

    //================================================ Set up the run
    settings->verbose                                 = -1;                                  // How verbose should the run be? -1 Means no verbal output at all.
    settings->setResolution                           ( 10.0 );                              // The resolution to which the calculations will be done. NOTE: Not necessarily the resolution of the structure!
    settings->addStructure                            ( "/Users/mysak/LMB/proshade/exp/demo/C2.pdb" );         // A path to the structure to be processed.
    settings->addStructure                            ( "/Users/mysak/LMB/proshade/exp/demo/testMap.map" );    // A path to the structure to be processed.
    settings->addStructure                            ( "/Users/mysak/LMB/proshade/exp/demo/C3.pdb" );         // A path to the structure to be processed.
    
    //================================================ Further useful settings
    settings->setMapResolutionChange                  ( false );                             // Should maps be re-sample to the computation resolution?
    settings->setPDBBFactor                           ( -1.0 );                              // Should all B-factors in a PDB file changed to this value? If no, set to negative value.
    settings->setBandwidth                            ( 0 );                                 // The spherical harmonics bandwidth to which to compute. Set to 0 for automatic determination.
    settings->setAngularResolution                    ( 0 );                                 // The resolution of the sphere mapping. Set to 0 for automatic determination.
    settings->setPhaseUsage                           ( true );                              // Use full maps, or Patterson-like maps?
    settings->setSphereDistances                      ( 0.0 );                               // The distance between spheres. Use 0.0 for automatic determination.
    settings->setIntegrationOrder                     ( 0 );                                 // The order of the Gauss-Legendre integration computation. Set to 0 for automatic determination.
    settings->setTaylorSeriesCap                      ( 10 );                                // Set the Taylor series approximation cap. 10 seems like a fast and accurate value, but feel free to change.
    settings->setNormalisation                        ( false );                             // Should internal map representation be normalised to mean 0 and standard deviation 1?
    settings->setMapInversion                         ( false );                             // Should all map positions x,y,z be swapped to -x,-y,-z? Use this only if your helices have the wrong hand as a result of first runs of map computation.
    settings->setMasking                              ( false );                             // Should maps be masked by blurring?
    settings->setMapReboxing                          ( false );                             // Should the structure be re-boxed? Required masking to be done in order to be meaningful.
    settings->setMapCentering                         ( false );                             // Move structure COM to the centre of map box?
    settings->setProgressiveSphereMapping             ( false );                             // Should smaller spheres be less sampled? It is considerably faster, but may sacrifice some (little) accuracy.
    settings->setEnergyLevelsComputation              ( true );                              // Should energy levels descriptor be computed, assuming Distances are required (irrelevant otherwise)?
    settings->setTraceSigmaComputation                ( true );                              // Should trace sigma descriptor be computed, assuming Distances are required (irrelevant otherwise)?
    settings->setRotationFunctionComputation          ( true );                              // Should rotation function descriptor be computed, assuming Distances are required (irrelevant otherwise)?
    settings->setEnLevShellWeight                     ( 1.0 );                               // The weighting of shell distances for energy levels descriptor.


    //================================================ All other (possibly other tasks related) settings
    settings->setMaskBlurFactor                       ( 350.0 );                             // If masking, what blur factor should be used? 350 seems to work for most maps.
    settings->setMaskIQR                              ( 3.0 );                               // Number of inter-quartile ranges from median to use as the masking threshold.
    settings->setMaskSaving                           ( false );                             // Should map mask be saved?
    settings->setMaskFilename                         ( "maskFile" );                        // The filename (no extension) to which the map masks will be saved into.
    settings->setBoundsSpace                          ( 3.0 );                               // The extra space in Angs to add to the minimal boundaries when re-boxing.
    settings->setBoundsThreshold                      ( 0 );                                 // If two boundaries are within this threshold, the smaller one will be increased to have the same value as the larger one.
    settings->setSameBoundaries                       ( false );                             // Make multiple structures have the same boundaries. This is useful for half-maps.
    settings->setOutputFilename                       ( "reBoxed" );                         // Filename to where re-boxed structure will be written to.
    settings->setExtraSpace                           ( 10.0 );                              // Extra space in Angs to be added when creating internap map representation. This helps avoid map effects from other cells.
    settings->setPeakNeighboursNumber                 ( 1 );                                 // Numer of points in each direction which needs to be lower in order for the central point to be considered a peak.
    settings->setPeakNaiveNoIQR                       ( 5.0 );                               // Peak searching threshold for too low peaks in number of inter-quartile ranges from median of the non-peak point values.
    settings->setMissingPeakThreshold                 ( 0.3 );                               // Fraction of peaks that can be missing for missing axis search to be initiated.
    settings->setAxisComparisonThreshold              ( 0.05 );                              // The dot product difference within which two axes are considered the same.
    settings->setRequestedSymmetry                    ( "" );                                // Which symmetry type (C,D,T,O or I) is requested to be detected? If none, then leave empty
    settings->setRequestedFold                        ( 0 );                                 // For C and D symmetries, which symmetry fold is requested to be detected? If none, leave 0.
    settings->setOverlaySaveFile                      ( "moved" );                           // Filename where the overlayed moving structure should be saved.

    //================================================ Print all the settings values
//    settings->printSettings                           ( );                                   // Prints all the ProSHADE_settings values. Mostly for debugging purposes.
    
    //================================================ Run ProSHADE
    ProSHADE_run* runProshade                         = new ProSHADE_run ( settings );         // This line runs the ProSHADE computations. It may take several seconds to finish the run.
    
    //================================================ Get results - these are already computed by the previous line, they are just copied by these commands.
    std::vector< proshade_double > energyDistances    = runProshade->getEnergyLevelsVector     ( ); // This is how the energy levels distances are accessed.
    std::vector< proshade_double > traceDistances     = runProshade->getTraceSigmaVector       ( ); // This is how the trace sigma distances are accessed.
    std::vector< proshade_double > rotFunDistances    = runProshade->getRotationFunctionVector ( ); // This is how the rotation function distances are accessed.
    
    //================================================ Print results
    std::cout << "Energy levels distances      : " << energyDistances.at(0) << " and " << energyDistances.at(1) << std::endl;
    std::cout << "Energy levels distances      : " << traceDistances.at(0)  << " and " << traceDistances.at(1)  << std::endl;
    std::cout << "Energy levels distances      : " << rotFunDistances.at(0) << " and " << rotFunDistances.at(1) << std::endl;

    //================================================ Release the settings and runProshade objects
    delete runProshade;
    delete settings;
    
    //================================================ DONE
    return EXIT_SUCCESS;
}
