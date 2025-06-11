import { getRedisClient } from '~/server/redis'

export default defineNitroPlugin(async () => {
    // console.log('Nitro plugin', nitroApp)
    const redis = await getRedisClient()

    let lastTilted = false
    setInterval(async () => {
        const tilt = await redis.get('T') === '1'

        if (tilt && !lastTilted) {
            console.log('post webhook')

            await $fetch('https://discord.com/api/webhooks/1377647283390255227/O4WDrKs9q8eljWGA3zVnHOkD_9W6qI1KIoGqsr0wAUdY3mrW5-dHNbXKuAmDGlHT_cs3', {
                method: 'POST',
                body: {
                    content: null,
                    embeds: [
                        {
                            title: 'Tilt Detection Notification',
                            description: '[!] A bin has been tilted!',
                            color: 16711680,
                        },
                    ],
                },
            })
        }

        lastTilted = tilt
    }, 2000)
})
