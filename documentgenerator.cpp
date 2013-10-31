#include "documentgenerator.h"

#include <QMap>
#include "docx-replacer/docxreplacer.h"

const QStringList DocumentGenerator::months = { "январь", "февраль", "март", "апрель", "май", "июнь", "июль", "август", "сентябрь", "октябрь",
                                           "ноябрь", "декабрь" };

const QString DocumentGenerator::studentLine = ""
        "            <w:tr w:rsidR=\"00917019\" w:rsidRPr=\"00917019\" w:rsidTr=\"00917019\">"
        "                <w:tc>"
        "                    <w:tcPr>"
        "                        <w:tcW w:w=\"534\" w:type=\"dxa\"/>"
        "                    </w:tcPr>"
        "                    <w:p w:rsidR=\"008C6194\" w:rsidRPr=\"00270E92\" w:rsidRDefault=\"00270E92\" w:rsidP=\"008C6194\">"
        "                        <w:pPr>"
        "                            <w:widowControl w:val=\"0\"/>"
        "                            <w:tabs>"
        "                                <w:tab w:val=\"center\" w:pos=\"284\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"2957\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"3947\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"5302\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"6946\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"8446\"/>"
        "                            </w:tabs>"
        "                            <w:autoSpaceDE w:val=\"0\"/>"
        "                            <w:autoSpaceDN w:val=\"0\"/>"
        "                            <w:adjustRightInd w:val=\"0\"/>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                                <w:lang w:val=\"en-US\"/>"
        "                            </w:rPr>"
        "                        </w:pPr>"
        "                        <w:r>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                                <w:lang w:val=\"en-US\"/>"
        "                            </w:rPr>"
        "                            <w:t>NN</w:t>"
        "                        </w:r>"
        "                    </w:p>"
        "                </w:tc>"
        "                <w:tc>"
        "                    <w:tcPr>"
        "                        <w:tcW w:w=\"2409\" w:type=\"dxa\"/>"
        "                    </w:tcPr>"
        "                    <w:p w:rsidR=\"008C6194\" w:rsidRPr=\"00270E92\" w:rsidRDefault=\"00270E92\" w:rsidP=\"008C6194\">"
        "                        <w:pPr>"
        "                            <w:widowControl w:val=\"0\"/>"
        "                            <w:tabs>"
        "                                <w:tab w:val=\"center\" w:pos=\"284\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"2957\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"3947\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"5302\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"6946\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"8446\"/>"
        "                            </w:tabs>"
        "                            <w:autoSpaceDE w:val=\"0\"/>"
        "                            <w:autoSpaceDN w:val=\"0\"/>"
        "                            <w:adjustRightInd w:val=\"0\"/>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                                <w:lang w:val=\"en-US\"/>"
        "                            </w:rPr>"
        "                        </w:pPr>"
        "                        <w:proofErr w:type=\"spellStart\"/>"
        "                        <w:r>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                                <w:lang w:val=\"en-US\"/>"
        "                            </w:rPr>"
        "                            <w:t>Lastname F.M.</w:t>"
        "                        </w:r>"
        "                        <w:proofErr w:type=\"spellEnd\"/>"
        "                    </w:p>"
        "                </w:tc>"
        "                <w:tc>"
        "                    <w:tcPr>"
        "                        <w:tcW w:w=\"993\" w:type=\"dxa\"/>"
        "                    </w:tcPr>"
        "                    <w:p w:rsidR=\"008C6194\" w:rsidRPr=\"00270E92\" w:rsidRDefault=\"008C6194\" w:rsidP=\"008C6194\">"
        "                        <w:pPr>"
        "                            <w:widowControl w:val=\"0\"/>"
        "                            <w:tabs>"
        "                                <w:tab w:val=\"center\" w:pos=\"284\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"2957\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"3947\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"5302\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"6946\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"8446\"/>"
        "                            </w:tabs>"
        "                            <w:autoSpaceDE w:val=\"0\"/>"
        "                            <w:autoSpaceDN w:val=\"0\"/>"
        "                            <w:adjustRightInd w:val=\"0\"/>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                                <w:lang w:val=\"en-US\"/>"
        "                            </w:rPr>"
        "                        </w:pPr>"
        "                    </w:p>"
        "                </w:tc>"
        "                <w:tc>"
        "                    <w:tcPr>"
        "                        <w:tcW w:w=\"850\" w:type=\"dxa\"/>"
        "                    </w:tcPr>"
        "                    <w:p w:rsidR=\"008C6194\" w:rsidRPr=\"00270E92\" w:rsidRDefault=\"008C6194\" w:rsidP=\"008C6194\">"
        "                        <w:pPr>"
        "                            <w:widowControl w:val=\"0\"/>"
        "                            <w:tabs>"
        "                                <w:tab w:val=\"center\" w:pos=\"284\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"2957\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"3947\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"5302\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"6946\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"8446\"/>"
        "                            </w:tabs>"
        "                            <w:autoSpaceDE w:val=\"0\"/>"
        "                            <w:autoSpaceDN w:val=\"0\"/>"
        "                            <w:adjustRightInd w:val=\"0\"/>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                                <w:lang w:val=\"en-US\"/>"
        "                            </w:rPr>"
        "                        </w:pPr>"
        "                    </w:p>"
        "                </w:tc>"
        "                <w:tc>"
        "                    <w:tcPr>"
        "                        <w:tcW w:w=\"1559\" w:type=\"dxa\"/>"
        "                    </w:tcPr>"
        "                    <w:p w:rsidR=\"008C6194\" w:rsidRPr=\"00917019\" w:rsidRDefault=\"008C6194\" w:rsidP=\"008C6194\">"
        "                        <w:pPr>"
        "                            <w:widowControl w:val=\"0\"/>"
        "                            <w:tabs>"
        "                                <w:tab w:val=\"center\" w:pos=\"284\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"2957\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"3947\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"5302\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"6946\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"8446\"/>"
        "                            </w:tabs>"
        "                            <w:autoSpaceDE w:val=\"0\"/>"
        "                            <w:autoSpaceDN w:val=\"0\"/>"
        "                            <w:adjustRightInd w:val=\"0\"/>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                            </w:rPr>"
        "                        </w:pPr>"
        "                    </w:p>"
        "                </w:tc>"
        "                <w:tc>"
        "                    <w:tcPr>"
        "                        <w:tcW w:w=\"851\" w:type=\"dxa\"/>"
        "                    </w:tcPr>"
        "                    <w:p w:rsidR=\"008C6194\" w:rsidRPr=\"00917019\" w:rsidRDefault=\"008C6194\" w:rsidP=\"008C6194\">"
        "                        <w:pPr>"
        "                            <w:widowControl w:val=\"0\"/>"
        "                            <w:tabs>"
        "                                <w:tab w:val=\"center\" w:pos=\"284\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"2957\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"3947\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"5302\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"6946\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"8446\"/>"
        "                            </w:tabs>"
        "                            <w:autoSpaceDE w:val=\"0\"/>"
        "                            <w:autoSpaceDN w:val=\"0\"/>"
        "                            <w:adjustRightInd w:val=\"0\"/>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                            </w:rPr>"
        "                        </w:pPr>"
        "                    </w:p>"
        "                </w:tc>"
        "                <w:tc>"
        "                    <w:tcPr>"
        "                        <w:tcW w:w=\"992\" w:type=\"dxa\"/>"
        "                    </w:tcPr>"
        "                    <w:p w:rsidR=\"008C6194\" w:rsidRPr=\"00917019\" w:rsidRDefault=\"008C6194\" w:rsidP=\"008C6194\">"
        "                        <w:pPr>"
        "                            <w:widowControl w:val=\"0\"/>"
        "                            <w:tabs>"
        "                                <w:tab w:val=\"center\" w:pos=\"284\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"2957\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"3947\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"5302\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"6946\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"8446\"/>"
        "                            </w:tabs>"
        "                            <w:autoSpaceDE w:val=\"0\"/>"
        "                            <w:autoSpaceDN w:val=\"0\"/>"
        "                            <w:adjustRightInd w:val=\"0\"/>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                            </w:rPr>"
        "                        </w:pPr>"
        "                    </w:p>"
        "                </w:tc>"
        "                <w:tc>"
        "                    <w:tcPr>"
        "                        <w:tcW w:w=\"1418\" w:type=\"dxa\"/>"
        "                    </w:tcPr>"
        "                    <w:p w:rsidR=\"008C6194\" w:rsidRPr=\"00917019\" w:rsidRDefault=\"008C6194\" w:rsidP=\"008C6194\">"
        "                        <w:pPr>"
        "                            <w:widowControl w:val=\"0\"/>"
        "                            <w:tabs>"
        "                                <w:tab w:val=\"center\" w:pos=\"284\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"2957\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"3947\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"5302\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"6946\"/>"
        "                                <w:tab w:val=\"center\" w:pos=\"8446\"/>"
        "                            </w:tabs>"
        "                            <w:autoSpaceDE w:val=\"0\"/>"
        "                            <w:autoSpaceDN w:val=\"0\"/>"
        "                            <w:adjustRightInd w:val=\"0\"/>"
        "                            <w:rPr>"
        "                                <w:rFonts w:ascii=\"Arial\" w:hAnsi=\"Arial\" w:cs=\"Arial\"/>"
        "                                <w:sz w:val=\"16\"/>"
        "                                <w:szCs w:val=\"16\"/>"
        "                            </w:rPr>"
        "                        </w:pPr>"
        "                    </w:p>"
        "                </w:tc>"
        "            </w:tr>";

bool DocumentGenerator::generateExamList(QString examListBlankPath, QString resultFilePath, QString semestr,
                                         QString academicYear, QString faculty, QString group, QString grade,
                                         QString prof, QString subject, QString teacher, QDate date,
                                         QStringList students)
{
    QMap<QString, QString> *replaceRules = new QMap<QString, QString>();
    replaceRules->insert("SEMESTR", semestr);
    replaceRules->insert("AYEAR", academicYear);
    replaceRules->insert("FACULTY", faculty);
    replaceRules->insert("GROUP", group);
    replaceRules->insert("GRADE", grade);
    replaceRules->insert("PROF", prof);
    replaceRules->insert("SUBJECT", subject);
    replaceRules->insert("TEACHER", teacher);
    replaceRules->insert("DD", QString::number(date.day()));
    replaceRules->insert("MONTH", months.at(date.month() - 1));
    replaceRules->insert("YEAR", QString::number(date.year()));
    QStringList studentLines;
    QString bufLine;
    for (int i = 0; i < students.count(); ++i) {
        bufLine = studentLine;
        bufLine.replace("NN", QString::number(i + 1));
        bufLine.replace("Lastname F.M.", students.at(i));
        studentLines.append(bufLine);
    }
    replaceRules->insert("STUDENTS", studentLines.join("\n"));
    return DocxReplacer::replaceInFile(examListBlankPath, replaceRules, resultFilePath);
}