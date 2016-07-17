#pragma once

#include "quickVtkPolyDataAlgorithm.hpp"

#include <vtkAbstractPolyDataReader.h>

namespace quick {

    namespace Vtk {

        class AbstractPolyDataReader : public PolyDataAlgorithm {
            Q_OBJECT
            Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChanged);
        private:
            static Qml::Register::AbstractClass<AbstractPolyDataReader> Register;
            vtkSmartPointer<vtkAbstractPolyDataReader> m_vtkAbstractPolyDataReader;
            QString m_fileName;
        public:
            AbstractPolyDataReader();
            AbstractPolyDataReader(AbstractPolyDataReader*);
            auto isValid() -> bool override;
            auto setVtkAbstractPolyDataReader(vtkSmartPointer<vtkAbstractPolyDataReader>) -> void;
            auto getVtkAbstractPolyDataReader() -> vtkSmartPointer<vtkAbstractPolyDataReader>;
            auto setFileName(const QString&) -> void;
            auto getFileName() -> QString;
            ~AbstractPolyDataReader();
        signals:
            void fileNameChanged();
        };
    }
}
