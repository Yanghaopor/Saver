//请求获取内存信息
    var xhrRE = new XMLHttpRequest();
    xhrRE.onreadystatechange = function(){if (xhrRE.readyState === XMLHttpRequest.DONE){
        if (xhrRE.status === 200) {
                var Data = String(xhrRE.responseText);
                var element = document.getElementById('reme_L');
                element.style.width = Data+'%';
                document.getElementById('RemData').innerHTML="内存占用"+Data+"%";
            } else {
                //alert("NoRemData");
            }
        }
    }
    var xhrREMAX =new XMLHttpRequest();
    xhrREMAX.onreadystatechange = function(){if (xhrREMAX.readyState === XMLHttpRequest.DONE){
        if (xhrREMAX.status === 200) {
             var remmax = String(xhrREMAX.responseText);
             document.getElementById('RemMax').innerHTML="内存大小"+remmax+"GB";
            } else {
                //alert("NoRemData");
            }
        }
    }
    var xhrCPU = new XMLHttpRequest();
    xhrCPU.onreadystatechange = function(){if (xhrCPU.readyState === XMLHttpRequest.DONE){
        if (xhrCPU.status === 200) {
                var Data = String(Number(xhrCPU.responseText)%100);
                var element = document.getElementById('cpuuser_L');
                element.style.width = Data+'%';
                    document.getElementById('CpuUserd').innerHTML="CPU占用"+Data+"%";
                    document.getElementById('CpuUserd').innerHTML="CPU占用"+Data+"%";
            } else {
                //alert("NoRemData");
            }
        }
    }
    var xhrCPUmhz = new XMLHttpRequest();
    xhrCPUmhz.onreadystatechange = function(){if (xhrCPUmhz.readyState === XMLHttpRequest.DONE){
        if (xhrCPUmhz.status === 200) {
                var Data = String(Number(xhrCPUmhz.responseText));
                var element = document.getElementById('cpuMhz_L');
                element.style.width = Data+'%';
                document.getElementById('CpuMhzf').innerHTML="CPU频率"+Data/10+"Ghz";
                //alert(Data)
                console.log("KL"+Data);
                
            } else {
                //alert("NoRemData");
            }
        }
    }

setInterval(function(){
    xhrRE.open('GET', 'http://127.0.0.1:80?IDGetReme=&', true);
    // 发送请求
    xhrRE.send();

    xhrREMAX.open('GET', 'http://127.0.0.1:80?IDGetRemeMax=&', true);
    // 发送请求
    xhrREMAX.send();

    xhrCPU.open('GET', 'http://127.0.0.1:80?IDGetCPUser=&', true);
    // 发送请求
    xhrCPU.send();

    xhrCPUmhz.open('GET', 'http://127.0.0.1:80?IDGetCPUmhz=&', true);
    // 发送请求
    xhrCPUmhz.send();
},500);