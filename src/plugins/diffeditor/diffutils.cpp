#include <QRegExp>
#include "texteditor/fontsettings.h"
static QList<RowData> readLines(const QString &patch,
//    const QRegExp lineRegExp(QLatin1String("(?:\\n)"                // beginning of the line
//                                           "([ -\\+\\\\])([^\\n]*)" // -, +, \\ or space, followed by any no-newline character
//                                           "(?:\\n|$)"));           // end of line or file
    const QStringList lines = patch.split(newLine);
        const QString line = lines.at(i);
        QChar firstCharacter = line.at(0);
            Diff diffToBeAdded(command, line.mid(1) + newLine);
static QList<ChunkData> readChunks(const QString &patch,
    const QRegExp chunkRegExp(QLatin1String(
                                  // beginning of the line
                              "(?:\\n|^)"
                                  // @@ -leftPos[,leftCount] +rightPos[,rightCount] @@
                              "@@ -(\\d+)(?:,\\d+)? \\+(\\d+)(?:,\\d+)? @@"
                                  // optional hint (e.g. function name)
                              "(\\ +[^\\n]*)?"
                                  // end of line (need to be followed by text line)
                              "\\n"));
    int pos = chunkRegExp.indexIn(patch);
    if (pos == 0) {
            const int leftStartingPos = chunkRegExp.cap(1).toInt();
            const int rightStartingPos = chunkRegExp.cap(2).toInt();
            const QString contextInfo = chunkRegExp.cap(3);
                const QString lines = patch.mid(endOfLastChunk,
                                                pos - endOfLastChunk);
            pos += chunkRegExp.matchedLength();
            endOfLastChunk = pos;
        } while ((pos = chunkRegExp.indexIn(patch, pos, QRegExp::CaretAtOffset)) != -1);
            const QString lines = patch.mid(endOfLastChunk);
static FileData readDiffHeaderAndChunks(const QString &headerAndChunks,
    QString patch = headerAndChunks;
    const QRegExp leftFileRegExp(QLatin1String(
                                     "(?:\\n|^)-{3} "        // "--- "
                                     "([^\\t\\n]+)"          // "fileName1"
                                     "(?:\\t[^\\n]*)*\\n")); // optionally followed by: \t anything \t anything ...)
    const QRegExp rightFileRegExp(QLatin1String(
                                      "^\\+{3} "              // "+++ "
                                      "([^\\t\\n]+)"          // "fileName2"
                                      "(?:\\t[^\\n]*)*\\n")); // optionally followed by: \t anything \t anything ...)
    const QRegExp binaryRegExp(QLatin1String("^Binary files ([^\\t\\n]+) and ([^\\t\\n]+) differ$"));

    // followed either by leftFileRegExp or by binaryRegExp
    if (leftFileRegExp.indexIn(patch) == 0) {
        patch.remove(0, leftFileRegExp.matchedLength());
        fileData.leftFileInfo.fileName = leftFileRegExp.cap(1);
        if (rightFileRegExp.indexIn(patch) == 0) {
            patch.remove(0, rightFileRegExp.matchedLength());
            fileData.rightFileInfo.fileName = rightFileRegExp.cap(1);
    } else if (binaryRegExp.indexIn(patch) == 0) {
        fileData.leftFileInfo.fileName = binaryRegExp.cap(1);
        fileData.rightFileInfo.fileName = binaryRegExp.cap(2);
        fileData.binaryFiles = true;
        readOk = true;
static QList<FileData> readDiffPatch(const QString &patch,
                                     bool *ok)
    const QRegExp diffRegExp(QLatin1String("(?:\\n|^)"          // new line of the beginning of a patch
                                           "("                  // either
                                           "-{3} "              // ---
                                           "[^\\t\\n]+"         // filename1
                                           "(?:\\t[^\\n]*)*\\n" // optionally followed by: \t anything \t anything ...
                                           "\\+{3} "            // +++
                                           "[^\\t\\n]+"         // filename2
                                           "(?:\\t[^\\n]*)*\\n" // optionally followed by: \t anything \t anything ...
                                           "|"                  // or
                                           "Binary files "
                                           "[^\\t\\n]+"         // filename1
                                           " and "
                                           "[^\\t\\n]+"         // filename2
                                           " differ"
                                           ")"));               // end of or
    int pos = diffRegExp.indexIn(patch);
    if (pos >= 0) { // git style patch
                const QString headerAndChunks = patch.mid(lastPos,
                                                          pos - lastPos);
            pos += diffRegExp.matchedLength();
        } while ((pos = diffRegExp.indexIn(patch, pos)) != -1);
        if (lastPos >= 0 && readOk) {
            const QString headerAndChunks = patch.mid(lastPos,
                                                      patch.count() - lastPos - 1);
static FileData readGitHeaderAndChunks(const QString &headerAndChunks,
    QString patch = headerAndChunks;
    const QRegExp newFileMode(QLatin1String("^new file mode \\d+\\n")); // new file mode octal
    const QRegExp deletedFileMode(QLatin1String("^deleted file mode \\d+\\n")); // deleted file mode octal
    const QRegExp modeChangeRegExp(QLatin1String("^old mode \\d+\\nnew mode \\d+\\n"));
    const QRegExp indexRegExp(QLatin1String("^index (\\w+)\\.{2}(\\w+)(?: \\d+)?(\\n|$)")); // index cap1..cap2(optionally: octal)
    if (newFileMode.indexIn(patch) == 0) {
        patch.remove(0, newFileMode.matchedLength());
    } else if (deletedFileMode.indexIn(patch) == 0) {
        fileData.fileOperation = FileData::DeleteFile;
        rightFileName = devNull;
        patch.remove(0, deletedFileMode.matchedLength());
    } else if (modeChangeRegExp.indexIn(patch) == 0) {
        patch.remove(0, modeChangeRegExp.matchedLength());
    if (indexRegExp.indexIn(patch) == 0) {
        fileData.leftFileInfo.typeInfo = indexRegExp.cap(1);
        fileData.rightFileInfo.typeInfo = indexRegExp.cap(2);
        patch.remove(0, indexRegExp.matchedLength());
        patch.remove(0, patch.indexOf(QLatin1Char('\n'), leftStart.count()) + 1);
            patch.remove(0, patch.indexOf(QLatin1Char('\n'), rightStart.count()) + 1);
static FileData readCopyRenameChunks(const QString &copyRenameChunks,
    QString patch = copyRenameChunks;
    const QRegExp indexRegExp(QLatin1String("^index (\\w+)\\.{2}(\\w+)(?: \\d+)?(\\n|$)")); // index cap1..cap2(optionally: octal)
        if (indexRegExp.indexIn(patch) == 0) {
            fileData.leftFileInfo.typeInfo = indexRegExp.cap(1);
            fileData.rightFileInfo.typeInfo = indexRegExp.cap(2);
            patch.remove(0, indexRegExp.matchedLength());
                patch.remove(0, patch.indexOf(QLatin1Char('\n'), leftStart.count()) + 1);
                    patch.remove(0, patch.indexOf(QLatin1Char('\n'), rightStart.count()) + 1);
static QList<FileData> readGitPatch(const QString &patch, bool *ok)
    const QRegExp simpleGitRegExp(QLatin1String("(?:\\n|^)diff --git a/([^\\n]+) b/\\1\\n")); // diff --git a/cap1 b/cap1
    const QRegExp similarityRegExp(QLatin1String(
                  "(?:\\n|^)diff --git a/([^\\n]+) b/([^\\n]+)\\n" // diff --git a/cap1 b/cap2
                  "(?:dis)?similarity index \\d{1,3}%\\n"          // similarity / dissimilarity index xxx% (100% max)
                  "(copy|rename) from \\1\\n"                      // copy / rename from cap1
                  "\\3 to \\2\\n"));                               // copy / rename (cap3) to cap2
        const int simpleGitPos = simpleGitRegExp.indexIn(patch, pos, QRegExp::CaretAtOffset);
        const int similarityPos = similarityRegExp.indexIn(patch, pos, QRegExp::CaretAtOffset);
        if (simpleGitPos < 0) {
            pos = similarityPos;
            simpleGitMatched = false;
        } else if (similarityPos < 0) {
            pos = simpleGitPos;
        pos = qMin(simpleGitPos, similarityPos);
        simpleGitMatched = (pos == simpleGitPos);
        do {
            if (endOfLastHeader > 0) {
                const QString headerAndChunks = patch.mid(endOfLastHeader,
                                                          pos - endOfLastHeader);
                if (!readOk)
                    break;
                fileDataList.append(fileData);
            }
                const QString fileName = simpleGitRegExp.cap(1);
                pos += simpleGitRegExp.matchedLength();
                endOfLastHeader = pos;
                lastLeftFileName = similarityRegExp.cap(1);
                lastRightFileName = similarityRegExp.cap(2);
                const QString operation = similarityRegExp.cap(3);
                pos += similarityRegExp.matchedLength();
                endOfLastHeader = pos;
        if (endOfLastHeader > 0 && readOk) {
            const QString headerAndChunks = patch.mid(endOfLastHeader,
                                                      patch.count() - endOfLastHeader - 1);

            FileData fileData;
            if (lastOperation == FileData::ChangeFile) {

                fileData = readGitHeaderAndChunks(headerAndChunks,
                                                  lastLeftFileName,
                                                  &readOk);
            } else {
                fileData = readCopyRenameChunks(headerAndChunks,
                                                lastOperation,
                                                lastLeftFileName,
                                                lastRightFileName,
                                                &readOk);
            }
            if (readOk)
                fileDataList.append(fileData);
        }
QList<FileData> DiffUtils::readPatch(const QString &patch, bool *ok)
    QString croppedPatch = patch;
    const QRegExp formatPatchEndingRegExp(QLatin1String("(\\n-- \\n\\S*\\n\\n$)"));
    const int pos = formatPatchEndingRegExp.indexIn(patch);
    if (pos != -1)
        croppedPatch = patch.left(pos + 1); // crop the ending for git format-patch
    fileDataList = readGitPatch(croppedPatch, &readOk);
        fileDataList = readDiffPatch(croppedPatch, &readOk);