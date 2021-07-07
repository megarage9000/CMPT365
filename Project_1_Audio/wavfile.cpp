#include "wavfile.h"

wavfile::wavfile(QString fileName)
{
    readWavFile(fileName);
}

template<class convertedType>
convertedType fromLittleEndian(QFile * file, int numBytes) {
    char * bits = (char *)malloc(numBytes);
    file->read(bits, numBytes);
    convertedType result = qFromLittleEndian<convertedType>((uchar*)bits);
    free(bits);
    return result;
}

void wavfile::readWavFile(QString fileName) {
    QFile wavFile(fileName);
    if(!wavFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    using namespace std;

    cout << "Reading WavFile...\n" ;

    // Read via: http://soundfile.sapp.org/doc/WaveFormat/

    // RIFF Chunk descriptor
    cout << "RIFF chunkId = " << wavFile.read(4).data() << endl;
    cout << "RIFF chunk size = " << fromLittleEndian<int>(&wavFile, 4) << endl;
    cout << "RIFF chunk format = " << wavFile.read(4).data() << endl;

    // FMT Sub-chunk
    cout << "FMT chunkId = " << wavFile.read(4).data() << endl;
    cout << "FMT chunkSize = " << fromLittleEndian<int>(&wavFile, 4) << endl;
    cout << "FMT audio format = " << fromLittleEndian<quint16>(&wavFile, 2) << endl;
    cout << "FMT num of channels = " << fromLittleEndian<quint16>(&wavFile, 2) << endl;
    cout << "FMT sample rate = " << fromLittleEndian<int>(&wavFile, 4) << endl;
    cout << "FMT byte rate = " << fromLittleEndian<int>(&wavFile, 4) << endl;
    cout << "FMT block align = " << fromLittleEndian<quint16>(&wavFile, 2) << endl;
    cout << "FMT bits per sample = " << fromLittleEndian<quint16>(&wavFile, 2) << endl;

    // Data Sub-chunk
    cout << "Data chunkId = " << wavFile.read(4).data() << endl;
    cout << "Data chunk size = " << fromLittleEndian<int>(&wavFile, 4) << endl;

    wavFile.close();
}






