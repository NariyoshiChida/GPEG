for i in 5; do
     RATIO=`echo "scale=3; $i*0.00090090" | bc`
     ./xmgen -f ${RATIO} -d -o ${i}M.xml
     echo "[${i}M done]"
done
