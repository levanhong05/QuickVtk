#include "quickVtkMapper2D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::Symbol::AbstractClass<Mapper2D> Mapper2D::Register;

        Mapper2D::Mapper2D(vtkSmartPointer<vtkMapper2D> vtkObject) : AbstractMapper(vtkObject) {
        }

        auto Mapper2D::getVtkObject() -> vtkSmartPointer<vtkMapper2D> {
            return vtkMapper2D::SafeDownCast(Algorithm::getVtkObject());
        }
    }
}
