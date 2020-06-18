
rem 各ngライブラリコピー用バッチ
rem 要ビルドイベント（ビルド後）設定

echo ######## copy_nglib ########
echo # Duplicate NG Library. Target=%TARGET_FILE_NAME%

set FOLDER_PATH=%SOLUTION_DIR%\Build\%PLATFORM%\ngLib\Lib\%CONFIGURATION%
set DUPE_PATH=%FOLDER_PATH%\%TARGET_FILE_NAME%
echo # FolderPath=%FOLDER_PATH%

mkdir "%FOLDER_PATH%"
copy "%TARGET_PATH%" "%DUPE_PATH%"
echo # Completed.
echo ############################
