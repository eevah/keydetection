#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <limits>
#include <cctype>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include "../stringbuilder.h"
#include "ShiftedKeyNotation.h"
#include "KeyCode.h"
#include "KeyRelation.h"

//using org::apache::log4j::Logger;


/// <summary>
/// This class represents a musical key.
///
/// Since there are a finite number of keys, a fly-weight pattern is used to conserve memory.  Therefore, this
/// class must remain immutable.  Methods which change the value of the key will return a new copy of a Key.
/// Furthermore, factory methods must be used to retrieve new values (i.e. getKey(...)).
/// </summary>
class Key // : public Serializable, public Comparable<Key*>
{

private:
    static const long long serialVersionUID = 0LL;

    ///////////////
    // CONSTANTS //
    ///////////////

    // 100 cents = 1 semitone = 1 half step
public:
//    static char semiTonesPerOctave;
    // the percent BPM shift equivalent to a change in 1 semitone pitch (a half-step, or 100 cents)
    static float bpmDifferencePerSemitone;

    // supported scale types/modes
    static int SCALE_UNKNOWN;
    static int SCALE_IONIAN; // standard major
    static int SCALE_AEOLIAN; // natural minor
    static int SCALE_LYDIAN; // major with raised 4th
    static int SCALE_MIXOLYDIAN; // major with lowered 7th
    static int SCALE_DORIAN; // minor with raised 6th
    static int SCALE_PHRYGIAN; // minor with lowered 2nd
    static int SCALE_LOCRIAN;

    static float ROOT_UNKNOWN;

    static std::vector<std::wstring> wellFormedKeys;

    static std::vector<std::wstring> advancedModes;

    static std::vector<std::wstring> keycodeSuffixes;

    static bool useFlatNotation;

    static Key *NO_KEY;

    ////////////
    // FIELDS //
    ////////////

private:
    float rootValue = ROOT_UNKNOWN; // ~0-12 range, corresponds with each note on the keyboard
    int scaleType = -1; // i.e. modal variation
    ShiftedKeyNotation *shiftedNotation; // the root value is exact and might be in between keys, this variable is used to display the shifted notation (i.e. Am+30)

    //////////////////
    // CONSTRUCTORS //
    //////////////////

    // for serialization only
public:
    Key();

private:
    Key(float rootValue, int scaleType);

    /////////////
    // GETTERS //
    /////////////

    // root note
public:
    virtual float getRootValue();
    virtual std::string getRootNoteDescription();

    // scale type
    virtual int getScaleType();
    virtual std::string getScaleTypeDescription();
    virtual bool isMinor();

    // shifted key
    virtual ShiftedKeyNotation *getShiftedKeyNotation();
    virtual std::string getShiftDescription();

    virtual std::string toString();
    virtual std::string toStringExact();

    // flat notation
    virtual std::string getKeyNotationFlat();
    virtual std::string getKeyNotationFlat(bool showDetails);

    // sharp notation
    virtual std::string getKeyNotationSharp();
    virtual std::string getKeyNotationSharp(bool showDetails);

    // custom notation
    virtual std::string getCustomKeyNotation();
    virtual std::string getCustomKeyNotation(bool showDetails);

    // key code
    virtual KeyCode *getKeyCode();

    virtual std::string getGroupSSLString();

    /// <summary>
    /// The ID3 safe notation excludes the shift and does not use keycodes or modes.
    /// </summary>
    virtual std::string getID3SafeKeyNotation();

    virtual std::string getShortKeyNotation();

    static std::string getPreferredKeyNotation(const std::string &key);
    virtual std::string getPreferredKeyNotation();
    virtual std::string getPreferredKeyNotation(bool showDetails);

    virtual bool isValid();

//    static bool isWellFormed(const std::wstring &input);

    static bool isValid(const std::wstring &key);

private:
    static bool isValidKeyCodeLetter(wchar_t c);

    /////////////
    // METHODS //
    /////////////

public:
    virtual Key *getShiftedKeyByBpmDifference(float bpm_difference);

    virtual Key *getShiftedKeyBySemitones(float semitones);

    static KeyRelation *getClosestKeyRelation(float sourceBpm, Key *sourceKey, float targetBpm, Key *targetKey);

    static KeyRelation *getClosestKeyRelation(float sourceBpm, Key *sourceKey, float targetBpm, Key *targetKey, float bpmDifference);

    /// <summary>
    /// This returns the shift required to transform the source scale type to the target scale type.
    /// </summary>
    /// <param name="int"> sourceScaleType </param>
    /// <param name="int"> targetScaleType </param>
    /// <returns> float shift from source to target </returns>
    static float getRelativeShift(int sourceScaleType, int targetScaleType);

    /// <summary>
    /// This returns the shift required to transform the scale type to ionian (major).
    /// </summary>
    /// <param name="int"> scaleType </param>
    /// <returns> float shift to ionian </returns>
private:
    static float getShiftToIonian(int scaleType);

    // changed to return just byte type for speed
public:
    virtual KeyRelation *getKeyRelationTo(Key *targetKey);

    virtual bool equals(Key *compare_key);
//    virtual int hashCode();

    virtual int compareTo(Key *compareKey);

    /////////////
    // PRIVATE //
    /////////////

private:
    void validateRootValue();

    static float validateRootValue(float rootValue);

    void appendMode(StringBuilder *result);

    int appendShift(StringBuilder *result);

    ////////////////////////
    // FLY WEIGHT PATTERN //
    ////////////////////////

public:
    static Key *getKey(const std::string &description);

    static Key *getKey(float rootValue, int scaleType);

private:
    static std::unordered_map<std::string, Key*> keyFlyWeights;

    static std::string calculatePrimaryKey(int shifted_key, int scaleType);

    static Key *checkFactory(float rootValue, int scaleType);

    ///////////////////////
    // FOR SERIALIZATION //
    ///////////////////////

public:
    virtual float geRrootValue();
    virtual void setRootValue(float rootValue);

    virtual void setScaleType(int scaleType);
    virtual ShiftedKeyNotation *getShiftedNotation();
    virtual void setShiftedNotation(ShiftedKeyNotation *shiftedNotation);
};
