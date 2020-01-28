using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class lazer_reflect : MonoBehaviour
{

    //private LineRenderer line;



    public int maxReflecionCount = 1;
    public float maxDistance = 100;
    public bool isUseingAButton = false;
    private bool isON = false;


    void Start()
    {
        //  line = GetComponent<LineRenderer>();

    }




    void OnDrawGizmos()
    {
        DrawLazerReflection(this.transform.position + this.transform.forward, this.transform.forward, maxReflecionCount);

    }

    private void DrawLazerReflection(Vector3 lazerPosition, Vector3 direction, int reflectionsRemaining)
    {
        if (isUseingAButton == false)
        {
            isON = true;
        }

        if (isUseingAButton == true)
        {
            if (!isON && GetComponentInParent<Active_Receiver>().isActive)
            {
                isON = true;
            }

            if ((isON && !GetComponentInParent<Active_Receiver>().isActive))
            {
                isON = false;
            }

            if (isON == true)
            {
                if (reflectionsRemaining == 0)
                {
                    return;
                }

                Vector3 startingPosition = lazerPosition;


                //raycast to detect reflection
                Ray ray = new Ray(lazerPosition, direction);
                RaycastHit hit;



                if (Physics.Raycast(ray, out hit, maxDistance))
                {


                    if (hit.transform.gameObject.tag == "reflect")
                    {
                        direction = Vector3.Reflect(direction, hit.normal);
                        lazerPosition = hit.point; // updates the hit point for mutiple reflections   

                    }
                    else if (hit.transform.gameObject.tag != "reflect")
                    {
                        lazerPosition += direction * maxDistance;
                        lazerPosition = hit.point;
                    }
                    else
                    {
                        lazerPosition += direction * maxDistance;
                    }
                }
                else
                {
                    lazerPosition += direction * maxDistance;
                }


                Gizmos.color = Color.red;
                Gizmos.DrawLine(startingPosition, lazerPosition);
                DrawLazerReflection(lazerPosition, direction, reflectionsRemaining - 1);

                //for drawing the lines in the game display
                //  line.SetPosition(0, startingPosition);
                //  line.SetPosition(1, lazerPosition + (direction * maxDistance * reflectionsRemaining));

                //  lineRenderer.enabled = true; //needed if it would bw disabled on start
            }

        }

    }
}
