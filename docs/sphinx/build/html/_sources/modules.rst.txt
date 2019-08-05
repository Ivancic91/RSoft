RSoftPython
===========

RSoftPython is a set of python code meant to easily facilitate some 
of the less computationally intensive proceedures of the RSoft project.
Eventually, we would like to wrap all of the C++ code in the RSoft 
project and make it pythonic. In the meantime, the following sets of 
code primarily allow a user to do four things:

* **Design your own structure functions**:
  In RSoftTools.RSoft, see OutputRSoftSF and the README on the RSoft 
  github page.

* **Train and test hyperplanes**:
  In RSoftTools.RSoft, see OpenDynamicsI, OpenSFI, OpenPlaneO, 
  SelectTrainingSet, Train, WritePlane, CloseDynamicsI, CloseSFI, 
  ClosePlaneO, and the tutorial in the README on the RSoft github 
  page.

* **Interact with structure functions directly**:
  In RSoftTools.RSoft, see OpenSFI, OpenSFO, CloseSFI, CloseSFO, 
  GetAngular, GetRadial, SetAngular, and SetRadial.

* **Find distances between particles and construct neighbor lists**
  **(slow)**: In RSoftTools.MDTools, see DeltaR and GetNList. These 
  are particularly helpful when one has periodic boundary conditions.


RSoftTools Classes
------------------

The following are classes within RSoftTools. They may be used by 
invoking the commands 'from RSoftTools import RSoft' and 
'from RSoftTools import MDTools'.

.. autosummary::
            :toctree: _autosummary

   RSoftTools.RSoft
   RSoftTools.MDTools

RSoft Methods
-------------

The following provides a list of functions that can be used on RSoft
objects.

.. autosummary::
            :toctree: _autosummary

   RSoftTools.RSoft.CloseDynamicsI
   RSoftTools.RSoft.ClosePlaneO
   RSoftTools.RSoft.CloseSFI
   RSoftTools.RSoft.CloseSFO
   RSoftTools.RSoft.GetAngular
   RSoftTools.RSoft.GetRadial
   RSoftTools.RSoft.OpenDynamicsI
   RSoftTools.RSoft.OpenPlaneO
   RSoftTools.RSoft.OpenSFI
   RSoftTools.RSoft.OpenSFO
   RSoftTools.RSoft.SelectTrainingSet
   RSoftTools.RSoft.SetAngular
   RSoftTools.RSoft.SetRadial
   RSoftTools.RSoft.Train
   RSoftTools.RSoft.WritePlane

RSoft Attributes
----------------

The following provides a list of attributes that can be used on RSoft
objects.

.. autosummary::
            :toctree: _autosummary

   RSoftTools.RSoft.etol_radial
   RSoftTools.RSoft.mus
   RSoftTools.RSoft.radial_Xs
   RSoftTools.RSoft.radial_Ys
   RSoftTools.RSoft.etol_angular
   RSoftTools.RSoft.xis
   RSoftTools.RSoft.lambdas
   RSoftTools.RSoft.zetas
   RSoftTools.RSoft.angular_Xs
   RSoftTools.RSoft.angular_Ys
   RSoftTools.RSoft.angular_Zs
   RSoftTools.RSoft.training_R
   RSoftTools.RSoft.training_NR

MDTools Methods
---------------

The following provides a list of functions that can be used on MDTool
objects.

.. autosummary::
            :toctree: _autosummary

   RSoftTools.MDTools.DeltaR
   RSoftTools.MDTools.GetNList
