/****************************************************************************
** Meta object code from reading C++ file 'gestionrendezvous.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../gestionrendezvous.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestionrendezvous.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGestionRendezvousENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSGestionRendezvousENDCLASS = QtMocHelpers::stringData(
    "GestionRendezvous",
    "nouveauPatient",
    "",
    "selectionnerPatient",
    "id",
    "appliquerTri",
    "critere",
    "modifierPatient",
    "supprimerPatient",
    "enregistrerPatient",
    "exporterPreConsultationPdf"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGestionRendezvousENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    1,   57,    2, 0x08,    2 /* Private */,
       5,    1,   60,    2, 0x08,    4 /* Private */,
       7,    1,   63,    2, 0x08,    6 /* Private */,
       8,    1,   66,    2, 0x08,    8 /* Private */,
       9,    0,   69,    2, 0x08,   10 /* Private */,
      10,    0,   70,    2, 0x08,   11 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GestionRendezvous::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSGestionRendezvousENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGestionRendezvousENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGestionRendezvousENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GestionRendezvous, std::true_type>,
        // method 'nouveauPatient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectionnerPatient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'appliquerTri'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'modifierPatient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'supprimerPatient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'enregistrerPatient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exporterPreConsultationPdf'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GestionRendezvous::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GestionRendezvous *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->nouveauPatient(); break;
        case 1: _t->selectionnerPatient((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->appliquerTri((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->modifierPatient((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->supprimerPatient((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->enregistrerPatient(); break;
        case 6: _t->exporterPreConsultationPdf(); break;
        default: ;
        }
    }
}

const QMetaObject *GestionRendezvous::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GestionRendezvous::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGestionRendezvousENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GestionRendezvous::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
