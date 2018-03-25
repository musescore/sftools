//=============================================================================
//  MuseScore
//  Linux Music Score Editor
//  $Id:$
//
//  Copyright (C) 2010 Werner Schweer and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <QtCore/QFile>
#include <QtCore/QTime>
#include "sfont.h"

bool smallSf = false;

//---------------------------------------------------------
//   usage
//---------------------------------------------------------

static void usage(const char* pname)
      {
      fprintf(stderr, "usage: %s [-flags] soundfont [outfile]\n", pname);
      fprintf(stderr, "   -z     compress sf\n");
      fprintf(stderr, "   -q qq  ogg quality\n");
      fprintf(stderr, "   -a nn  amplification in dB before ogg compression\n");
      fprintf(stderr, "   -x     xml output\n");
      fprintf(stderr, "   -c     c output\n");
      fprintf(stderr, "   -p nn  preset\n");
      fprintf(stderr, "   -d     dump presets\n");
      fprintf(stderr, "   -s     create small sf (one instrument/preset), pan to 0\n");
      fprintf(stderr, "   -S nn  ogg serial number\n");
      }

//---------------------------------------------------------
//   main
//---------------------------------------------------------

int main(int argc, char* argv[])
      {
      bool xml  = false;
      bool code = false;
      bool dump = false;
      bool compress = false;
      double oggQuality = 0.3;
      double oggAmp = -1.0;
      qint64 oggSerial = std::numeric_limits<qint64>::max();

      QList<int> presets;

      QTime t;
      t.start();
      fprintf(stderr, "%s: convert sound file\n", argv[0]);

      int c;
      while ((c = getopt(argc, argv, "xcp:dS:szq:a:")) != EOF) {
            switch(c) {
                  case 'x':
                        xml = true;
                        break;
                  case 'c':
                        code = true;
                        break;
                  case 'p':
                        presets.append(atoi(optarg));
                        break;
                  case 'd':
                        dump = true;
                        break;
                  case 'S':
                        oggSerial = atoi(optarg);
                        break;
                  case 's':
                        smallSf = true;
                        break;
                  case 'z':
                        compress = true;
                        break;
                  case 'q':
                        oggQuality = atof(optarg);
                        break;
                  case 'a':
                        oggAmp = atof(optarg);
                        break;
                  default:
                        usage(argv[0]);
                        exit(1);
                  }
            }
      const char* pname = argv[0];

      argc -= optind;
      argv += optind;
      if (xml && (argc != 2)) {
            usage(pname);
            exit(2);
            }
      if ((code && (argc != 1)) || (dump && argc != 1)) {
            usage(pname);
            exit(3);
            }
      if (!xml && !code && !dump && !compress) {
            usage(pname);
            exit(4);
            }

      SoundFont sf(argv[0]);

      if (!sf.read()) {
            fprintf(stderr, "sf read error\n");
            exit(3);
            }

      if (code) {
            if (presets.isEmpty())
                  sf.writeCode();
            else
                  sf.writeCode(presets);
            }
      else if (dump)
            sf.dumpPresets();
      else if (compress) {
            QFile fo(argv[1]);
            if (!fo.open(QIODevice::WriteOnly)) {
                  fprintf(stderr, "cannot open <%s>\n", argv[2]);
                  exit(2);
                  }
            if (xml)
                  sf.writeXml(&fo);
            else
                  sf.write(&fo, oggQuality, oggAmp, oggSerial);
            fo.close();
            }
      qDebug("Soundfont converted in: %d ms", t.elapsed());
      return 0;
      }

