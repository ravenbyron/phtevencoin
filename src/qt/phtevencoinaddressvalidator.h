// Copyright (c) 2011-2014 The Phtevencoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PHTEVENCOIN_QT_PHTEVENCOINADDRESSVALIDATOR_H
#define PHTEVENCOIN_QT_PHTEVENCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class PhtevencoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit PhtevencoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Phtevencoin address widget validator, checks for a valid phtevencoin address.
 */
class PhtevencoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit PhtevencoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // PHTEVENCOIN_QT_PHTEVENCOINADDRESSVALIDATOR_H
