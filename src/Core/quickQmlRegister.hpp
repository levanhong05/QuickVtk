#pragma once

#include <functional>

#include <QtQml>
#include <QList>
#include <QString>
#include <QMetaObject>
#include <QMetaProperty>

namespace quick {
    namespace Qml {
        namespace Register {
            namespace MakeSymbol {
                auto Enum(const QString&, const QString&) -> void;
                auto Class(QMetaObject) -> void;
                auto AbstractClass(QMetaObject) -> void;
            }

            auto Init() -> void;
#ifdef _MSC_VER
            struct Queue {
                static auto GetList()->QList<std::function<void(void)>>&;
            };
#endif
            template <class T>
            struct Controller {
                Controller() {
                    auto initializer = [](){
                        qmlRegisterType<T>();
                        T::Create();
                    };
#ifdef _MSC_VER
                    Queue::GetList().append(initializer);
#else
                    initializer();
#endif
                }
            };

            template <class T>
            struct Type {
                Type() {
                    auto initializer = []() {
                        qmlRegisterType<T>();
                    };
#ifdef _MSC_VER
                    Queue::GetList().append(initializer);
#else
                    initializer();
#endif
                }
            };

            template <class T>
            struct VtkAbstractClass {
                VtkAbstractClass() {
                    auto initializer = []() {
                        QMetaObject metaObject = T::staticMetaObject;
                        auto name = QString(metaObject.className());
                        auto prefix = name.section("::", 1, 1);
                        auto className = name.section("::", 2, 2);

                        qmlRegisterUncreatableType<T>(prefix.toStdString().c_str(), 1, 0, className.toStdString().c_str(), "abstract class \'" + className + "\' can not be instantiated.");

                        for (auto i = 0; i < metaObject.enumeratorCount(); ++i) {
                            MakeSymbol::Enum(prefix, metaObject.enumerator(i).name());
                        }

                        MakeSymbol::AbstractClass(metaObject);
                    };
#ifdef _MSC_VER
                    Queue::GetList().append(initializer);
#else
                    initializer();
#endif
                }
            };

            template <class T>
            struct VtkClass {
                VtkClass() {
                    auto initializer = []() {
                        QMetaObject metaObject = T::staticMetaObject;
                        auto name = QString(metaObject.className());
                        auto prefix = name.section("::", 1, 1);
                        auto className = name.section("::", 2, 2);

                        qmlRegisterType<T>(prefix.toStdString().c_str(), 1, 0, className.toStdString().c_str());

                        for (auto i = 0; i < metaObject.enumeratorCount(); ++i) {
                            MakeSymbol::Enum(prefix, metaObject.enumerator(i).name());
                        }

                        MakeSymbol::Class(metaObject);
                    };
#ifdef _MSC_VER
                    Queue::GetList().append(initializer);
#else
                    initializer();
#endif
                }
            };
        }
    }
}