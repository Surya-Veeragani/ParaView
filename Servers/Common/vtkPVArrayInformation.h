/*=========================================================================

  Program:   ParaView
  Module:    vtkPVArrayInformation.h

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPVArrayInformation - Data array information like type.
// .SECTION Description
// This objects is for eliminating direct access to vtkDataObjects
// by the "client".  Only vtkPVPart and vtkPVProcessModule should access
// the data directly.  At the moment, this object is only a container
// and has no useful methods for operating on data.
// Note:  I could just use vtkDataArray objects and store the range
// as values in the array.  This would eliminate this object.

#ifndef __vtkPVArrayInformation_h
#define __vtkPVArrayInformation_h

#include "vtkPVInformation.h"

class vtkClientServerStream;

class VTK_EXPORT vtkPVArrayInformation : public vtkPVInformation
{
public:
  static vtkPVArrayInformation* New();
  vtkTypeRevisionMacro(vtkPVArrayInformation, vtkPVInformation);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // DataType is the string name of the data type: VTK_FLOAT ...
  // the value "VTK_VOID" means that different processes have different types.
  vtkSetMacro(DataType, int);
  vtkGetMacro(DataType, int);

  vtkSetStringMacro(Name);
  vtkGetStringMacro(Name);

  // Description:
  // Changing the number of components clears the ranges back to the default.
  void SetNumberOfComponents(int numComps);
  vtkGetMacro(NumberOfComponents, int);

  // Description:
  // There is a range for each component.
  // Range for component -1 is the range of the vector magnitude.
  // The number of components should be set before these ranges.
  void SetComponentRange(int comp, double min, double max);
  void SetComponentRange(int comp, double *range)
    { this->SetComponentRange(comp, range[0], range[1]);}
  double *GetComponentRange(int component);
  void GetComponentRange(int comp, double *range);

  // Description:
  // Returns 1 if the array can be combined.
  // It must have the same name and number of components.
  int Compare(vtkPVArrayInformation *info);

  // Description:
  // Merge (union) ranges into this object.
  void AddRanges(vtkPVArrayInformation *info);

  void DeepCopy(vtkPVArrayInformation *info);

  // Description:
  // Transfer information about a single object into this object.
  virtual void CopyFromObject(vtkObject*);

  // Description:
  // Merge another information object.
  virtual void AddInformation(vtkPVInformation*);

  // Description:
  // Manage a serialized version of the information.
  virtual void CopyToStream(vtkClientServerStream*) const;
  virtual void CopyFromStream(const vtkClientServerStream*);

  // Description:
  // If IsPartial is true, this array is in only some of the
  // parts of a multi-block dataset. By default, IsPartial is
  // set to 0.
  vtkSetMacro(IsPartial, int);
  vtkGetMacro(IsPartial, int);

protected:
  vtkPVArrayInformation();
  ~vtkPVArrayInformation();

  int IsPartial;
  int DataType;
  int NumberOfComponents;
  char *Name;
  double *Ranges;

  vtkPVArrayInformation(const vtkPVArrayInformation&); // Not implemented
  void operator=(const vtkPVArrayInformation&); // Not implemented
};

#endif
