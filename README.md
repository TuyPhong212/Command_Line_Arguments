# Command_Line_Arguments
Chương trình sử dụng Jenkins Pipeline để build chương trình C sử dụng GCC
# Tạo file "Dockerfile" có chưa GCC Compiler
File Dockerfile có nội dung như sau:

    FROM jenkins/jenkins:lts-jdk11
    # if we want to install via apt
    USER root
    RUN apt-get update && apt-get install -y build-essential
    # drop back to the regular jenkins user - good practice
    USER jenkins

# Build Doceker image
    docker build -t jenkins/jenkins:lts-jdk11 -f Dockerfile .
# Run And Create Jenkins
This will store the workspace in /var/jenkins_home. All Jenkins data lives in there - including plugins and configuration. You will probably want to make that an explicit volume so you can manage it and attach to another container for upgrades.

    docker run -p 8080:8080 -p 50000:50000 --restart=on-failure -v jenkins_home:/var/jenkins_home jenkins/jenkins:lts-jdk11
# Đặng nhập vào Jenkins:
    Servers localhost:8080
    Acount: admin
    Password : get from "/var/jenkins_home/secrets/initialAdminPassword" on Docker Desktop
# Tạo Jenkinsfile
          pipeline {
        agent any
        
        stages {
            stage("Clean Up"){
                steps {
                    deleteDir()
                }
            }
            stage('Checkout') {
                steps {
                    // Đặt đường dẫn của mã nguồn chương trình C
                    sh "git clone https://github.com/TuyPhong212/Command_Line_Arguments.git"
                }
            }
            
            stage('Build') {
                steps {
                    // Thực hiện các lệnh build chương trình C
                    sh '''
                    cd $PWD/Command_Line_Arguments
                    gcc -o Command_Line_Arguments Command_Line_Arguments.c
                    '''
                }
            }
            
            stage('Test') {
                steps {
                    // Thực hiện các lệnh kiểm tra chương trình C
                    sh '''
                    cd $PWD/Command_Line_Arguments
                    ./Command_Line_Arguments Argv1 Argv2
                    '''
                }
            }
    
            stage('Push') {
                steps {
                    // Thực hiện các push file đã biên dịch lên GIT
                    // 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
                    sh '''
                    cd $PWD/Command_Line_Arguments
                    git add Command_Line_Arguments
                    git commit -m "Command_Line_Arguments"
                    git push -u origin main
                    Username for 'https://github.com':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
                    '''
                }
            }
        }
    }
    // git remote set-url origin https://SHA256:IN85Yt0fecgcWOJMmcoj9Tc24pu0wAkBCjoT3XzGEaw@github.com/cuongmaidt2/Command_Line_Arguments.git


