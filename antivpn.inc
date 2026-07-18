/*
    Anti VPN/Proxy Powerd by https://proxycheck.io/
    https://github.com/Pawn-Hubs/antivpn
*/

#if defined iAntiVPN
    #endinput
#endif

#if !defined _INC_a_http
    #error adicione #include <a_http> em cima da #include <antivpn>
    #endinput
#endif

#define iAntiVPN

forward AntiVPN(playerid, response_code, data[]);
public AntiVPN(playerid, response_code, data[])
{
	static nome[MAX_PLAYERS], string[124];
	GetPlayerName(playerid, nome, sizeof(nome));	
	if(response_code == 200)
	{	
	    if(substr(data, "\"proxy\": \"yes\""))
		{
			format(string, sizeof(string), "{F70000}[ANTI-VPN]: {FFE700}%s(%d) foi {F70000}Kickado {FFFFFF}por Suspeita de {F70000}VPN/Proxy", nome, playerid);
	    	SendClientMessageToAll(-1, string);
            printf("[ANTI-VPN]: %s Suspeito de VPN/Proxy.", nome);
	    	Kick(playerid);
		}
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
    static ip[16], string[59];
    GetPlayerIp(playerid, ip, sizeof(ip));	
    format(string, sizeof(string), "proxycheck.io/v2/%s?vpn=1&asn=1", ip);
    HTTP(playerid, HTTP_GET, string, "", "AntiVPN");
    #if defined vpn_OnPlayerConnect
        return vpn_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect VPN_OnPlayerConnect
#if defined VPN_OnPlayerConnect
    forward VPN_OnPlayerConnect(playerid);
#endif

static substr(const source[], const find[])
{
    new src = strlen(source);
    new enc = strlen(find);  
    for(new i = 0; i <= src - enc; i++)
    {
        static match = true;
        for(new j = 0; j < enc; j++)
        {
            if(source[i+j] != find[j])
            {
                match = false;
                break;
            }
        }
        if(match) return true;
    }
    return false; // poderia ser bool:substr, porem, da warning, mas tanto faz, 1 e 0 sao tratados como true e false na maioria dos casos.
}
