void setupSD() {
  pinMode(SDPin, OUTPUT);
  //LightOn(1);
  Serial.println(F("setupSD start"));
  while (!SD.begin(SDPin)) {
    Serial.println(F("begin failure"));
    LightOn(2);
    root.close();
    delay(500);
    SDavail = false;
    //return;
  }
  delay(1);
  root.close();
  delay(1);
  root = SD.open("/");
  if (root) {
    Serial.println(root.name());
  }
  delay(1);
  GetFileInfo(root);
  //m_CurrentFilename = m_FileNames[0];
  Serial.println(F("SD rooted!"));
  Sort(m_FileNames, m_NumberOfFiles);
}

void GetFileInfo(File dir) {
  String CurrentFilename = "";
  int fileCount = 0;
  while (1) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files

      entry.close();
      break;
    }
    else {
      if (entry.isDirectory()) {
        //GetNextFileName(root);
      }
      else {
        CurrentFilename = entry.name();
        if (CurrentFilename.endsWith(F(".bmp")) || CurrentFilename.endsWith(F(".BMP")) ) { // find bmps only
          delay(2);
          if (CurrentFilename.length() == 5) {
            Serial.print(F("currentFilename : "));
            Serial.println(CurrentFilename);
            m_FileNames[fileCount] = CurrentFilename.substring(0, 1);
            fileCount++;
            if (fileCount >= FILELIMIT) {
              entry.close();
              break;
            }
          }
        }
      }
    }
    entry.close();
  }
  m_NumberOfFiles = fileCount;
  Serial.print(F("fileCount : "));
  Serial.println(fileCount);
  Serial.println(F("SD sweeped"));
}


//void Sort(String *filenames, int n, unsigned int *filedurs) {
void Sort(String *filenames, int n) {
  for (int i = 1; i < n; ++i) {
    String j = filenames[i];
    //int jdur = filedurs[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < filenames[k]); k--) {
      filenames[k + 1] = filenames[k];
      //  filedurs[k + 1] =  filedurs[k];
    }
    filenames[k + 1] = j;
    //   filedurs[k + 1] = jdur;
  }
  Serial.println(F("Sorted"));
  for (int l = 0; l < m_NumberOfFiles; l++) {
    Serial.print(F("No. \t"));
    Serial.print(l);
    Serial.print(F(" : \t"));
    Serial.println(m_FileNames[l] + F(".BMP"));
    //  Serial.print(" : ");
    //  Serial.println(m_FileDur[l]);
  }
}


